.source tests/parsing/parse.tc
.class  public shit
.super  java/lang/Object


.method public <init>V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method

.method public static main(I)I
	.limit locals 10
	.limit stack 10
.end method

.method public static x(I)C
	.limit locals 10
	.limit stack 10
.end method

.method public static functwo(III)I
	.limit locals 10
	.limit stack 10
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V
.end method

