.source testfiles/factorial.tc
.class  public s
.super  java/lang/Object


.method public <init>()V
	aload_0
	invokenonvirtual java/lang/Object/<init>()V
	return
.end method

.method public static main([Ljava/lang/String;)V
	.limit locals 20
	.limit stack 7

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore_2

	aload_2
	invokevirtual java/util/Scanner/nextInt()I
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	iload_0
	bipush 1
	if_icmpeq label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpne else_label0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "IF\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	goto end_if0
else_label0:
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "ElSE\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
end_if0:
	bipush 0
	return
.end method

