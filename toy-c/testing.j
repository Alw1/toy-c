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
	bipush 1
	bipush 1
	if_icmpeq label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
loop:
	iconst_0
	if_icmpne end_loop
loop:
end_loop:
	break:
	iload_0
	bipush 0
	if_icmpeq label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpne else_label
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "WORKS?"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V
	goto end_if
else_label:
end_if:
	break:
	return
.end method

