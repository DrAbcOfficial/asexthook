"""Exercise update decisions and real Git publication without GitHub writes."""
import importlib.util
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch
import urllib.error

SCRIPT = Path(__file__).resolve().parents[1] / "scripts/upstream.py"
SPEC = importlib.util.spec_from_file_location("upstream", SCRIPT)
upstream = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(upstream)
SHA_A = "a" * 40
SHA_B = "b" * 40
RELEASE = {"id": 42, "tag_name": "v1.0", "html_url": "https://github.com/metamod-svencoop/asext/releases/tag/v1.0"}


class Decisions(unittest.TestCase):
    def candidate(self, release=RELEASE, exists=False):
        return upstream.release_candidate("owner/template", "main", SHA_A, release,
                                          lambda tag: exists, lambda tag: (SHA_A, SHA_B))

    def test_no_release(self):
        self.assertIsNone(self.candidate(None))

    def test_existing_release(self):
        self.assertIsNone(self.candidate(exists=True))

    def test_prerelease_and_draft(self):
        for key in ("prerelease", "draft"):
            self.assertIsNone(self.candidate(dict(RELEASE, **{key: True})))

    def test_new_release_has_immutable_refs(self):
        candidate = self.candidate()
        self.assertEqual("asext-release-42", candidate["template_tag"])
        self.assertEqual(SHA_B, candidate["metamod_sha"])

    def test_bad_commit_is_rejected(self):
        with self.assertRaises(ValueError):
            upstream.sha("main")

    def test_api_only_treats_404_as_missing(self):
        for status in (404, 403, 500):
            error = urllib.error.HTTPError("https://api.github.com/test", status, "error", {}, None)
            with patch.object(upstream.urllib.request, "urlopen", side_effect=error):
                if status == 404:
                    self.assertIsNone(upstream.api("test", missing_ok=True))
                else:
                    with self.assertRaises(RuntimeError):
                        upstream.api("test", missing_ok=True)


class Publication(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="asexthook-git-test-")
        self.addCleanup(self.temporary.cleanup)
        self.base = Path(self.temporary.name)
        self.environment = patch.dict(upstream.os.environ, {"GIT_ALLOW_PROTOCOL": "file",
            "GIT_AUTHOR_NAME": "Test", "GIT_AUTHOR_EMAIL": "test@example.com",
            "GIT_COMMITTER_NAME": "Test", "GIT_COMMITTER_EMAIL": "test@example.com"})
        self.environment.start()
        self.addCleanup(self.environment.stop)
        self.root = self.base / "template"
        self.root.mkdir()
        upstream.git(self.root, "init", "-b", "main")
        for name in ("asext", "metamod"):
            source = self.base / name
            source.mkdir()
            upstream.git(source, "init", "-b", "main")
            (source / "value").write_text("old")
            upstream.git(source, "add", "value")
            upstream.git(source, "commit", "-m", "initial")
            upstream.git(self.root, "submodule", "add", str(source), name)
        upstream.git(self.root, "commit", "-m", "initial template")
        self.remote = self.base / "origin.git"
        upstream.git(self.base, "init", "--bare", str(self.remote))
        upstream.git(self.root, "remote", "add", "origin", str(self.remote))
        upstream.git(self.root, "push", "origin", "main")
        self.initial = upstream.git(self.root, "rev-parse", "HEAD").stdout.strip()
        commits = []
        for name in ("asext", "metamod"):
            source = self.base / name
            (source / "value").write_text("new")
            upstream.git(source, "add", "value")
            upstream.git(source, "commit", "-m", "new dependency")
            commits.append(upstream.git(source, "rev-parse", "HEAD").stdout.strip())
        upstream.git(self.base / "asext", "tag", "-a", "v1.0", "-m", "annotated release")
        self.candidate = upstream.release_candidate("owner/template", "main", self.initial,
            RELEASE, lambda tag: False, lambda tag: tuple(commits))

    def publish(self, validated=True):
        return upstream.publish(self.root, self.candidate, "owner/template", "main", validated)

    def remote_tags(self):
        return upstream.git(self.root, "ls-remote", "--tags", "origin").stdout

    def test_annotated_release_tag_resolves_to_commit(self):
        def api(path, missing_ok=False):
            if path.endswith("releases/latest"):
                return RELEASE
            if path.endswith("commits/main"):
                return {"sha": self.candidate["metamod_sha"]}
            return None
        with patch.object(upstream, "api", side_effect=api):
            candidate = upstream.detect(self.root, "owner/template", "main")
        self.assertEqual(self.candidate["asext_sha"], candidate["asext_sha"])

    def test_validation_failure_does_not_push(self):
        with self.assertRaises(ValueError):
            self.publish(validated=False)
        self.assertEqual("", self.remote_tags())
        self.assertEqual(self.initial, upstream.git(self.remote, "rev-parse", "main").stdout.strip())

    def test_update_and_repeat_are_idempotent(self):
        self.assertEqual("published", self.publish())
        published = upstream.git(self.remote, "rev-parse", "main").stdout.strip()
        self.assertNotEqual(self.initial, published)
        self.assertEqual(published, upstream.git(self.remote, "rev-parse", "asext-release-42").stdout.strip())
        for name in ("asext", "metamod"):
            tree = upstream.git(self.remote, "ls-tree", "main", name).stdout
            self.assertIn(self.candidate[name + "_sha"], tree)
        self.candidate["base_sha"] = published
        self.assertEqual("already-published", self.publish())

    def test_unchanged_dependencies_still_create_release_tag(self):
        for name in ("asext", "metamod"):
            self.candidate[name + "_sha"] = upstream.git(self.root / name, "rev-parse", "HEAD").stdout.strip()
        self.assertEqual("published", self.publish())
        self.assertEqual(self.initial, upstream.git(self.remote, "rev-parse", "main").stdout.strip())
        self.assertIn("refs/tags/asext-release-42", self.remote_tags())

    def advance_branch(self, working_tree):
        (working_tree / "unrelated").write_text("concurrent work")
        upstream.git(working_tree, "add", "unrelated")
        upstream.git(working_tree, "commit", "-m", "unrelated work")
        upstream.git(working_tree, "push", "origin", "HEAD:refs/heads/main")

    def test_stale_default_branch_skips_update(self):
        self.advance_branch(self.root)
        self.assertEqual("stale", self.publish())
        self.assertEqual("", self.remote_tags())

    def test_atomic_push_rejects_race_without_publishing_tag(self):
        rival = self.base / "rival"
        upstream.git(self.base, "clone", "--branch", "main", str(self.remote), str(rival))
        real_git = upstream.git

        def racing_git(root, *args, **kwargs):
            if args[:2] == ("push", "--atomic"):
                with patch.object(upstream, "git", real_git):
                    self.advance_branch(rival)
            return real_git(root, *args, **kwargs)

        with patch.object(upstream, "git", side_effect=racing_git):
            with self.assertRaises(subprocess.CalledProcessError):
                self.publish()
        self.assertEqual("", self.remote_tags())


if __name__ == "__main__":
    unittest.main()
