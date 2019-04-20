#include <iostream>
#include <string>
#include <cctype>

/*
 * Parses given string as an unsigned integer in specified radix.
 * If input string is invalid, returns -1
 */
int parse_int(std::string const &token) {
    unsigned int value = 0;
    unsigned int radix = DEFAULT_RADIX;
    for (char c : token) {
        if (std::isdigit(c) && c - '0' < radix) {
            (value *= 10) += c - '0';
        } else {
            return -1;
        }
    }
    return value;
}

unsigned char const parse_int_code = {
    0x55,                   	        // push   %rbp
    0x48, 0x89, 0xe5,             	    // mov    %rsp,%rbp
    0x48, 0x83, 0xec, 0x40          	// sub    $0x40,%rsp
    48 89 7d c8          	// mov    %rdi,-0x38(%rbp)
    64 48 8b 04 25 28 00 	// mov    %fs:0x28,%rax
    00 00
    48 89 45 f8          	// mov    %rax,-0x8(%rbp)
    31 c0                	// xor    %eax,%eax
    c7 45 d8 00 00 00 00 	// movl   $0x0,-0x28(%rbp)
    c7 45 dc 0a 00 00 00 	// movl   $0xa,-0x24(%rbp)
    48 8b 45 c8          	// mov    -0x38(%rbp),%rax
    48 89 45 f0          	// mov    %rax,-0x10(%rbp)
    48 8b 45 f0          	// mov    -0x10(%rbp),%rax
    48 89 c7             	// mov    %rax,%rdi
    e8 00 00 00 00       	// callq  3d <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x3d>
    48 89 45 e0          	// mov    %rax,-0x20(%rbp)
    48 8b 45 f0          	// mov    -0x10(%rbp),%rax
    48 89 c7             	// mov    %rax,%rdi
    e8 00 00 00 00       	// callq  4d <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x4d>
    48 89 45 e8          	// mov    %rax,-0x18(%rbp)
    48 8d 55 e8          	// lea    -0x18(%rbp),%rdx
    48 8d 45 e0          	// lea    -0x20(%rbp),%rax
    48 89 d6             	// mov    %rdx,%rsi
    48 89 c7             	// mov    %rax,%rdi
    e8 00 00 00 00       	// callq  64 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x64>
    84 c0                	// test   %al,%al
    74 5f                	// je     c7 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xc7>
    48 8d 45 e0          	// lea    -0x20(%rbp),%rax
    48 89 c7             	// mov    %rax,%rdi
    e8 00 00 00 00       	// callq  74 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x74>
    0f b6 00             	// movzbl (%rax),%eax
    88 45 d7             	// mov    %al,-0x29(%rbp)
    0f be 45 d7          	// movsbl -0x29(%rbp),%eax
    83 e8 30             	// sub    $0x30,%eax
    83 f8 09             	// cmp    $0x9,%eax
    77 3a                	// ja     c0 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xc0>
    0f be 45 d7          	// movsbl -0x29(%rbp),%eax
    83 e8 30             	// sub    $0x30,%eax
    39 45 dc             	// cmp    %eax,-0x24(%rbp)
    76 2e                	// jbe    c0 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xc0>
    8b 55 d8             	// mov    -0x28(%rbp),%edx
    89 d0                	// mov    %edx,%eax
    c1 e0 02             	// shl    $0x2,%eax
    01 d0                	// add    %edx,%eax
    01 c0                	// add    %eax,%eax
    89 45 d8             	// mov    %eax,-0x28(%rbp)
    48 8d 45 d8          	// lea    -0x28(%rbp),%rax
    8b 08                	// mov    (%rax),%ecx
    0f be 55 d7          	// movsbl -0x29(%rbp),%edx
    01 ca                	// add    %ecx,%edx
    83 ea 30             	// sub    $0x30,%edx
    89 10                	// mov    %edx,(%rax)
    48 8d 45 e0          	// lea    -0x20(%rbp),%rax
    48 89 c7             	// mov    %rax,%rdi
    e8 00 00 00 00       	// callq  be <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xbe>
    eb 91                	// jmp    51 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x51>
    b8 ff ff ff ff       	// mov    $0xffffffff,%eax
    eb 03                	// jmp    ca <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xca>
    8b 45 d8             	// mov    -0x28(%rbp),%eax
    48 8b 75 f8          	// mov    -0x8(%rbp),%rsi
    64 48 33 34 25 28 00 	// xor    %fs:0x28,%rsi
    00 00
    74 05                	// je     de <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xde>
    e8 00 00 00 00       	// callq  de <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xde>
    c9                   	// leaveq
    c3                   	// retq
};

/*
 * Converts given unsigned integer value to a string in specified radix.
 */
std::string to_string(unsigned int value) {
    std::string res;
    res.push_back('0' + value);
    return res;
}

int main(int argc, char *argv[]) {

    auto func = reinterpret_cast<int (*)(std::string const &)>(parse_int_code);
    std::cout << "Radix: " << DEFAULT_RADIX << "\n" << argv[1] << " to " << (*func)(argv[1]) << std::endl;

}
