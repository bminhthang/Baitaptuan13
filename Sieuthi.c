#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node {
    char customer_name[100]; // Tên khách hàng
    int product_A;  // Số lượng sản phẩm A 
    int total_payment;  // Tổng số tiền thanh toán 
    struct Node* next;  // Con trỏ đến node tiếp theo 
};
struct Queue {
    struct Node* front;
    struct Node* rear;
};
void initQueue(struct Queue* q) {
    q->front = q->rear = NULL;
}

// Thêm một khách hàng vào hàng đợi
void enqueue(struct Queue* q, const char* name, int product_A, int total_payment) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->customer_name, name);
    newNode->product_A = product_A;
    newNode->total_payment = total_payment;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Loại bỏ khách hàng khỏi hàng đợi
struct Node* dequeue(struct Queue* q) {
    if (q->front == NULL) return NULL;
    
    struct Node* temp = q->front;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }

    return temp;
}

// Tính tổng số tiền thu được từ tất cả khách hàng 
int total_payment_in_queue(struct Queue* q) {
    int total = 0;
    struct Node* current = q->front;
    while (current != NULL) {
        total += current->total_payment;
        current = current->next;
    }
    return total;
}

// Đếm số lượng sản phẩm A đã bán
int count_product_a(struct Queue* q) {
    int count = 0;
    struct Node* current = q->front;
    while (current != NULL) {
        count += current->product_A;
        current = current->next;
    }
    return count;
}

// Kiểm tra xem hàng đợi có trống không
int isEmpty(struct Queue* q) {
    return q->front == NULL;
}
int main() {
    struct Queue queue;
    initQueue(&queue);

    int n;
    printf("Nhập số lượng khách hàng: ");
    scanf("%d", &n);
    getchar(); 
    // Nhập thông tin khách hàng
    for (int i = 0; i < n; i++) {
        char name[100];
        int product_A, total_payment;

        // Nhập tên 
        printf("\nNhập tên khách hàng %d: ", i + 1);
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';  // Xóa ký tự newline nếu có

        // Nhập số lượng sản phẩm A
        printf("Nhập số lượng sản phẩm A của khách hàng %d: ", i + 1);
        scanf("%d", &product_A);

        // Nhập tổng số tiền thanh toán
        printf("Nhập tổng số tiền thanh toán của khách hàng %d: ", i + 1);
        scanf("%d", &total_payment);
        getchar(); // Đọc ký tự newline còn sót lại

        // Thêm khách hàng vào hàng đợi
        enqueue(&queue, name, product_A, total_payment);
    }

    // Tính tổng số tiền thu được
    int total_money = total_payment_in_queue(&queue);
    printf("\nTổng số tiền thu được: %d đồng\n", total_money);

    // Xác định số lượng sản phẩm A đã bán
    int product_a_count = count_product_a(&queue);
    printf("Số lượng sản phẩm A đã bán: %d\n", product_a_count);

    // Loại bỏ khách hàng sau khi thanh toán
    while (!isEmpty(&queue)) {
        struct Node* customer = dequeue(&queue);
        printf("Khách hàng %s đã thanh toán %d đồng và đã được loại bỏ khỏi hàng đợi\n",
               customer->customer_name, customer->total_payment);
        free(customer);
    }
    return 0;
}

   