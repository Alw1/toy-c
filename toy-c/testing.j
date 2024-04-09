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

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore_1

	bipush 0
	istore_0
	iload_0
	bipush 10
	if_icmpne label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
loop:
	iconst_0
	if_icmpne end_loop
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "X"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload_0
	bipush 1
	iadd
	istore_0
loop:
end_loop:
	return
.end method

