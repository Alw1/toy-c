.source testfiles/random.tc
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
	astore_1

	bipush 0
	istore 4
	bipush 9
	istore 5
	bipush 5
	istore 6
	aload_1
	invokevirtual java/util/Scanner/nextInt()I
	istore 5
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload 5
	invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
	invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V
