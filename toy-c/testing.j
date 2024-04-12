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
	astore_3

	bipush 5
	invokestatic s/factorial(I)I
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	bipush 0
	return
.end method

.method public static factorial(I)I
	.limit locals 20
	.limit stack 7

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore_3

	iload_0
	bipush 0
	iload_0
	ior
	if_icmpeq label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	bipush 1
	if_icmpeq label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpne else_label
	bipush 1
	ireturn
	goto end_if
else_label:
	iload_0
	iload_0
	bipush 1
	isub
	invokestatic s/factorial(I)I
	imul
	ireturn
end_if:
	break:
.end method

