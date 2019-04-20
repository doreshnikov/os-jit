/*
 * Returns given unsigned integer value string representation in specified radix.
 */
char const *to_radix(unsigned int value) {
    unsigned int i = 0;
    unsigned int radix = DEFAULT_RADIX;
    char *digits = new char[33];
    while (value > 0) {
        unsigned int digit = value % radix;
        digits[i] =  digit > 9 ? 'a' + digit - 10 : '0' + digit;
        value /= radix;
        i++;
    }
    digits[i--] = 0;
    int j = 0;
    while (i > j) {
        char t = digits[i];
        digits[i--] = digits[j];
        digits[j++] = t;
    }
    return digits;
}

// @formatter:off
unsigned char to_radix_code[] = {
	0x55,                                     	// push   %rbp
	0x48, 0x89, 0xe5,                         	// mov    %rsp,%rbp
	0x48, 0x83, 0xec, 0x30,                   	// sub    $0x30,%rsp
	0x89, 0x7d, 0xdc,                         	// mov    %edi,-0x24(%rbp)
	0xc7, 0x45, 0xe8, 0x00, 0x00, 0x00, 0x00, 	// movl   $0x0,-0x18(%rbp)
	0xc7, 0x45, 0xf0, 0x0a, 0x00, 0x00, 0x00, 	// movl   $0xa,-0x10(%rbp)
	0xbf, 0x21, 0x00, 0x00, 0x00,             	// mov    $0x21,%edi
	0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  23 <_Z8to_radixj+0x23>
	0x48, 0x89, 0x45, 0xf8,                   	// mov    %rax,-0x8(%rbp)
	0x83, 0x7d, 0xdc, 0x00,                   	// cmpl   $0x0,-0x24(%rbp)
	0x74, 0x46,                               	// je     73 <_Z8to_radixj+0x73>
	0x8b, 0x45, 0xdc,                         	// mov    -0x24(%rbp),%eax
	0xba, 0x00, 0x00, 0x00, 0x00,             	// mov    $0x0,%edx
	0xf7, 0x75, 0xf0,                         	// divl   -0x10(%rbp)
	0x89, 0x55, 0xf4,                         	// mov    %edx,-0xc(%rbp)
	0x83, 0x7d, 0xf4, 0x09,                   	// cmpl   $0x9,-0xc(%rbp)
	0x76, 0x0a,                               	// jbe    4b <_Z8to_radixj+0x4b>
	0x8b, 0x45, 0xf4,                         	// mov    -0xc(%rbp),%eax
	0x83, 0xc0, 0x57,                         	// add    $0x57,%eax
	0x89, 0xc1,                               	// mov    %eax,%ecx
	0xeb, 0x08,                               	// jmp    53 <_Z8to_radixj+0x53>
	0x8b, 0x45, 0xf4,                         	// mov    -0xc(%rbp),%eax
	0x83, 0xc0, 0x30,                         	// add    $0x30,%eax
	0x89, 0xc1,                               	// mov    %eax,%ecx
	0x8b, 0x55, 0xe8,                         	// mov    -0x18(%rbp),%edx
	0x48, 0x8b, 0x45, 0xf8,                   	// mov    -0x8(%rbp),%rax
	0x48, 0x01, 0xd0,                         	// add    %rdx,%rax
	0x88, 0x08,                               	// mov    %cl,(%rax)
	0x8b, 0x45, 0xdc,                         	// mov    -0x24(%rbp),%eax
	0xba, 0x00, 0x00, 0x00, 0x00,             	// mov    $0x0,%edx
	0xf7, 0x75, 0xf0,                         	// divl   -0x10(%rbp)
	0x89, 0x45, 0xdc,                         	// mov    %eax,-0x24(%rbp)
	0x83, 0x45, 0xe8, 0x01,                   	// addl   $0x1,-0x18(%rbp)
	0xeb, 0xb4,                               	// jmp    27 <_Z8to_radixj+0x27>
	0x8b, 0x45, 0xe8,                         	// mov    -0x18(%rbp),%eax
	0x8d, 0x50, 0xff,                         	// lea    -0x1(%rax),%edx
	0x89, 0x55, 0xe8,                         	// mov    %edx,-0x18(%rbp)
	0x89, 0xc2,                               	// mov    %eax,%edx
	0x48, 0x8b, 0x45, 0xf8,                   	// mov    -0x8(%rbp),%rax
	0x48, 0x01, 0xd0,                         	// add    %rdx,%rax
	0xc6, 0x00, 0x00,                         	// movb   $0x0,(%rax)
	0xc7, 0x45, 0xec, 0x00, 0x00, 0x00, 0x00, 	// movl   $0x0,-0x14(%rbp)
	0x8b, 0x45, 0xec,                         	// mov    -0x14(%rbp),%eax
	0x39, 0x45, 0xe8,                         	// cmp    %eax,-0x18(%rbp)
	0x76, 0x50,                               	// jbe    e7 <_Z8to_radixj+0xe7>
	0x8b, 0x55, 0xe8,                         	// mov    -0x18(%rbp),%edx
	0x48, 0x8b, 0x45, 0xf8,                   	// mov    -0x8(%rbp),%rax
	0x48, 0x01, 0xd0,                         	// add    %rdx,%rax
	0x0f, 0xb6, 0x00,                         	// movzbl (%rax),%eax
	0x88, 0x45, 0xe7,                         	// mov    %al,-0x19(%rbp)
	0x8b, 0x45, 0xec,                         	// mov    -0x14(%rbp),%eax
	0x48, 0x63, 0xd0,                         	// movslq %eax,%rdx
	0x48, 0x8b, 0x45, 0xf8,                   	// mov    -0x8(%rbp),%rax
	0x48, 0x8d, 0x0c, 0x02,                   	// lea    (%rdx,%rax,1),%rcx
	0x8b, 0x45, 0xe8,                         	// mov    -0x18(%rbp),%eax
	0x8d, 0x50, 0xff,                         	// lea    -0x1(%rax),%edx
	0x89, 0x55, 0xe8,                         	// mov    %edx,-0x18(%rbp)
	0x89, 0xc2,                               	// mov    %eax,%edx
	0x48, 0x8b, 0x45, 0xf8,                   	// mov    -0x8(%rbp),%rax
	0x48, 0x01, 0xc2,                         	// add    %rax,%rdx
	0x0f, 0xb6, 0x01,                         	// movzbl (%rcx),%eax
	0x88, 0x02,                               	// mov    %al,(%rdx)
	0x8b, 0x45, 0xec,                         	// mov    -0x14(%rbp),%eax
	0x8d, 0x50, 0x01,                         	// lea    0x1(%rax),%edx
	0x89, 0x55, 0xec,                         	// mov    %edx,-0x14(%rbp)
	0x48, 0x63, 0xd0,                         	// movslq %eax,%rdx
	0x48, 0x8b, 0x45, 0xf8,                   	// mov    -0x8(%rbp),%rax
	0x48, 0x01, 0xc2,                         	// add    %rax,%rdx
	0x0f, 0xb6, 0x45, 0xe7,                   	// movzbl -0x19(%rbp),%eax
	0x88, 0x02,                               	// mov    %al,(%rdx)
	0xeb, 0xa8,                               	// jmp    8f <_Z8to_radixj+0x8f>
	0x48, 0x8b, 0x45, 0xf8,                   	// mov    -0x8(%rbp),%rax
	0xc9,                                     	// leaveq 
	0xc3,                                     	// retq   
};
// @formatter:on