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
	astore 5

	bipush 10
	istore_0
	aload 5
	invokevirtual java/util/Scanner/nextInt()I
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "! = "
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokestatic s/recursiveFactorial(I)I
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream.print(Ljava/lang/String;)V
	bipush 30
	invokestatic s/counter(I)I
	bipush 91
	invokestatic s/isPrime(I)I
	bipush 6
	invokestatic s/isPrime(I)I
	bipush 7
	invokestatic s/isPrime(I)I
	bipush 0
	return
.end method

.method public static recursiveFactorial(I)I
	.limit locals 20
	.limit stack 7

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore 5

	iload_0
	bipush 1
	if_icmpge label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpeq if_label0
	bipush 1
	ireturn
if_label0:
	iload_0
	iload_0
	bipush 1
	isub
	invokestatic s/recursiveFactorial(I)I
	imul
	ireturn
.end method

.method public static counter(I)I
	.limit locals 20
	.limit stack 7

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore 6

	bipush 0
	istore_1
loop0:
	iload_1
	iload_0
	if_icmplt label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpne end_loop0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload_1
	bipush 1
	iadd
	istore_1
	goto loop0
end_loop0:
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "END OF LOOP\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	iload_1
	ireturn
.end method

.method public static isPrime(I)I
	.limit locals 20
	.limit stack 7

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore 6

	bipush 2
	istore_1
loop0:
	iload_1
	iload_0
	bipush 2
	idiv
	if_icmplt label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpne end_loop0
	iload_0
	bipush 1
	irem
	bipush 0
	if_icmpeq label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	iconst_0
	if_icmpeq if_label1
if_label1:
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc " is a prime number\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	bipush 1
	ireturn
	goto loop0
end_loop0:
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc " isn't a prime number\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	bipush 1
	ineg
	ireturn
.end method

