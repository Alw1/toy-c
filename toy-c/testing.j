.source tests/parsing/parse.tc
.class  public 
.super  java/lang/Object


.method public <init>()V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method

.method public static main([Ljava/lang/String;)V
I	.limit locals 10
	.limit stack 10

	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V
	return
.end method

