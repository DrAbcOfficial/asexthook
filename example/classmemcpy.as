class Foo{
	int a;
	int b;
	int c;
	//........
	int zzzz;
}
Foo a,b;
a.a = 114;
a.b = 514;
//....
a.zzz = 810;

g_EngineFuncs.ClassMemcpy(a, b);

//114
say(b.a);

//Kabooooom
g_EngieFuncs.ClassMemcpy(Bar(), b);