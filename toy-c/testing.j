.source testfiles/factorial.tc
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

	bipush 5
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	bipush 2
	bipush 5
	imul
	bipush 10
	imul
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	bipush 10
	bipush 2
	irem
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	bipush 9
	bipush 2
	irem
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	bipush 10
	bipush 2
	isub
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	bipush 0
	return
.end method

.method public static factorial(I)I
	.limit locals 10
	.limit stack 10

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore_1

	bipush 1
	istore_1
	bipush 2
	istore_2
	iload_2
	iload_0
	if_icmple label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
loop:
	iconst_0
	if_icmpne end_loop
	iconst_0
	iload_1
	iload_2
	imul
	istore_1
	iload_2
	bipush 1
	iadd
	istore_2
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	goto loop
end_loop:
break:
	iload_1
	ireturn
.end method

