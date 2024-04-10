.source testfiles/loop.tc
.class  public s
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

	bipush 10
	istore_0
loop:
	iload_0
	bipush 0
	if_icmpge label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpne end_loop
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	iload_0
	bipush 1
	isub
	istore_0
	goto loop
end_loop:
break:
	bipush 1
	return
.end method

