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

	bipush 0
	istore_0
	bipush 1
	istore_1
	iload_0
	iload_1
	if_icmplt label_0
	iconst_1
	goto label_1
label_0:
	iconst_0
label_1:
	istore_0
	return
.end method

