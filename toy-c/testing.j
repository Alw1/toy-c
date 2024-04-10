.source testfiles/test.tc
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
	istore_1
	bipush 2
	istore_2
	bipush 1
	invokestatic test/x(I)I
	istore_1
	return
.end method

.method public static x(I)I
	.limit locals 10
	.limit stack 10

	new java/util/Scanner
	dup
	getstatic java/lang/System/in Ljava/io/InputStream;
	invokespecial java/util/Scanner/<init>(Ljava/io/InputStream;)V
	astore_1

	bipush 0
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	ldc "IN THIS FUNCTION\n"
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
	bipush 1
	ireturn
.end method

