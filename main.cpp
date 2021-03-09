#include <iostream>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    long long int n = rand() % 8 + 3;
    long long int arr[n][n];
    cout << "Array: \n";
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 9 + 1;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nNew array c++: \n";
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) cout << "1 ";
            else if (j == n-1-i) cout << "1 ";
            else cout << "0 ";
        }
        cout << endl;
    }
    long long *ptr_array = &arr[0][0];
    long long *ctr_array = &arr[n/2][n/2];
    long long *end_array = &arr[n-1][n-1];
    asm (
        "mov %[ptr_array], %%rbx\n\t"
        "mov %[ptr_array], %%rcx\n\t"
        "mov $8, %%rax\n\t"
        "mulq %[n]\n\t"
        "add $8, %%rax\n\t"
        "add %%rax, %%rcx\n\t"
        "sub $16, %%rcx\n\t"
        "add %%rax, %[ptr_array]\n\t"
        "push $1\n\t"
        "pop (%%rbx)\n\t"

        "loop_start:\n\t"
            "add $8, %%rbx\n\t"
            "cmp %%rbx, %[ptr_array]\n\t"
            "je prt_one\n\t"
            "cmp %%rbx, %%rcx\n\t"
            "je end_one\n\t"
            "push $0\n\t"
            "pop (%%rbx)\n\t"
            "cmp %%rbx, %[end_array]\n\t"
            "je end\n\t"
        "jmp loop_start\n\t"

        "prt_one:\n\t"
            "push $1\n\t"
            "pop (%%rbx)\n\t"
            "cmp %%rcx, %[ctr_array]\n\t"
            "je prt_end_one\n\t"
            "add %%rax, %[ptr_array]\n\t"
            "cmp %%rbx, %[end_array]\n\t"
            "je end\n\t"
        "jmp loop_start\n\t"

        "end_one:\n\t"
            "push $1\n\t"
            "pop (%%rbx)\n\t"
            "add %%rax, %%rcx\n\t"
            "sub $16, %%rcx\n\t"
            "cmp %%rbx, %[end_array]\n\t"
            "je end\n\t"
        "jmp loop_start\n\t"

        "prt_end_one:\n\t"
            "add %%rax, %[ptr_array]\n\t"
            "add %%rax, %%rcx\n\t"
            "sub $16, %%rcx\n\t"
        "jmp loop_start\n\t"

        "end:\n\t"
        :
        :[ptr_array]"m"(ptr_array), [end_array]"m"(end_array), [ctr_array]"m"(ctr_array), [n]"m"(n)
        :"%rax", "%rbx", "%rcx", "%rdx"
    );

    cout << "\nNew array asm: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
