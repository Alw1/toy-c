.source tests/parsing/parse.tc
.class  public test
.super  java/lang/Object


.method public <init>()V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method

.method public static main([Ljava/lang/String;)V
	.limit locals 10
	.limit stack 10

	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V
	bipush 1
	bipush 2
	bipush 3
	ldc "HELLO"
	load some shit here later 0
	return
.end method

