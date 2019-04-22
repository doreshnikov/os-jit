/*
 * Returns the integer logarithm of given unsigned integer `value` with specified `base`.
 */
unsigned int logarithm(unsigned int value) {
    unsigned int i = 0;
    unsigned int base = DEFAULT_VALUE;
    while (value > 0) {
        unsigned int digit = value % base;
        value /= base;
        i++;
    }
    return i;
}

// @formatter:off
unsigned char logarithm_code[] = {
	0x55,                                     	// push   %rbp
	0x48, 0x89, 0xe5,                         	// mov    %rsp,%rbp
	0x89, 0x7d, 0xec,                         	// mov    %edi,-0x14(%rbp)
	0xc7, 0x45, 0xf4, 0x00, 0x00, 0x00, 0x00, 	// movl   $0x0,-0xc(%rbp)
	0xc7, 0x45, 0xf8, 0x02, 0x00, 0x00, 0x00, 	// movl   $0x2,-0x8(%rbp)
	0x83, 0x7d, 0xec, 0x00,                   	// cmpl   $0x0,-0x14(%rbp)
	0x74, 0x22,                               	// je     3d <_Z9logarithmj+0x3d>
	0x8b, 0x45, 0xec,                         	// mov    -0x14(%rbp),%eax
	0xba, 0x00, 0x00, 0x00, 0x00,             	// mov    $0x0,%edx
	0xf7, 0x75, 0xf8,                         	// divl   -0x8(%rbp)
	0x89, 0x55, 0xfc,                         	// mov    %edx,-0x4(%rbp)
	0x8b, 0x45, 0xec,                         	// mov    -0x14(%rbp),%eax
	0xba, 0x00, 0x00, 0x00, 0x00,             	// mov    $0x0,%edx
	0xf7, 0x75, 0xf8,                         	// divl   -0x8(%rbp)
	0x89, 0x45, 0xec,                         	// mov    %eax,-0x14(%rbp)
	0x83, 0x45, 0xf4, 0x01,                   	// addl   $0x1,-0xc(%rbp)
	0xeb, 0xd8,                               	// jmp    15 <_Z9logarithmj+0x15>
	0x8b, 0x45, 0xf4,                         	// mov    -0xc(%rbp),%eax
	0x5d,                                     	// pop    %rbp
	0xc3,                                     	// retq   
};
// @formatter:on
