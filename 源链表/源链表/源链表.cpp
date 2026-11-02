//项目名称：简单的通讯录管理程序
//项目功能：实现对通讯录的增删改查功能，包括添加联系人、删除联系人、修改联系人信息和查询联系人信息。
//项目作者：苏敏
//项目日期：2026年10月26日

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// 定义联系人结构体
typedef struct {
    char name[50]; // 姓名
    char phone[12]; // 电话号码
    struct Birthday {
        int year;
        int month;
        int day;
    } birthday;
    int age; // 年龄
} Contact;

/*函数功能：计算联系人年龄
  输入参数：const Contact* contact（联系人信息指针）、int* age（年龄指针）
  返回值：成功返回true，失败返回false,bool类型
*/
static bool calculateAge(const Contact* contact, int* age) {
    time_t now = time(NULL);
    struct tm* currentDate = localtime(&now);
    if (currentDate == NULL) {
        fprintf(stderr, "无法获取当前日期\n");
        return false;
    }

    *age = currentDate->tm_year + 1900 - contact->birthday.year;
    if (currentDate->tm_mon + 1 < contact->birthday.month ||
        (currentDate->tm_mon + 1 == contact->birthday.month &&
            currentDate->tm_mday < contact->birthday.day)) {
        --*age;
    }
    return true;
}

//定义通讯录节点结构体
typedef struct Node {
    Contact data;
    struct Node* next;
} Node;

/*函数功能：初始化一个空的通讯录链表
  输入参数：无
  返回值：Node*类型，指向空链表头节点的指针
*/
Node* initContactList() {
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL)
        fprintf(stderr, "内存分配失败\n");
    else
        head->next = NULL;
    return head;
}

/*函数功能：采用头插法向通讯录链表中添加联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、Contact data（要添加的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool addContact(Node* head, Contact data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return false;
    }
    node->data = data;
    node->next = head->next;
    head->next = node;
    return true;
}

/*函数功能：采用尾插法向通讯录链表中添加联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、Contact data（要添加的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool addContactAtTail(Node* head, Contact data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return false;
    }
    node->data = data;
    node->next = NULL;
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return true;
}

/*函数功能：删除通讯录链表中的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、char* name（要删除的联系人姓名）
  返回值：成功返回true，失败返回false,bool类型
*/
bool deleteContact(Node* head, char* name) {
    Node* current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->data.name, name) == 0) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
            return true;
        }
        current = current->next;
    }
    return false; // 未找到联系人
}

/*函数功能：修改通讯录链表中的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、char*   name（要修改的联系人姓名）、Contact newData（新的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool modifyContact(Node* head, char* name, Contact newData) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            current->data = newData;
            return true;
        }
        current = current->next;
    }
    return false; // 未找到联系人
}

/*函数功能：查询通讯录链表中的联系人信息（姓名）
  输入参数：Node* head（通讯录链表头节点指针）、char name[]（要查询的联系人姓名）
  返回值：成功返回地址，失败返回空指针,void*类型
*/
void* searchContact(Node* head, char name[]) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            return &current->data;
        }
        current = current->next;
    }
    return NULL; // 未找到联系人
}

/*函数功能：查询通讯录链表中的联系人信息（电话号码）
  输入参数：Node* head（通讯录链表头节点指针）、char phone[]（要查询的联系人电话号码）
  返回值：成功返回地址，失败返回空指针,void*类型
*/
void* searchContactByPhone(Node* head, char phone[]) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.phone, phone) == 0) {
            return &current->data;
        }
        current = current->next;
    }
    return NULL; // 未找到联系人
}

/*函数功能：输出单个人的联系人信息
  输入参数：Contact contact（联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool printContact(Contact contact) {
    printf("姓名: %s\n", contact.name);
    printf("电话号码: %s\n", contact.phone);
    printf("出生日期: %d-%d-%d\n", contact.birthday.year, contact.birthday.month, contact.birthday.day);
    printf("年龄: %d\n", contact.age);
    return true;
}

/*函数功能：输出所有人的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）
  返回值：成功返回true，失败返回false,bool类型
*/
bool printAllContacts(Node* head) {
    Node* current = head->next;
    while (current != NULL) {
        printContact(current->data);
        current = current->next;
    }
    return true;
}

/*函数功能：在指定联系人后面插入新的联系人信息
  输入参数：Node* head（通讯录链表头节点指针）、char* name（指定联系人姓名）、Contact newData（新的联系人信息）
  返回值：成功返回true，失败返回false,bool类型
*/
bool insertContactAfter(Node* head, char* name, Contact newData) {
    Node* current = head->next;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            Node* node = (Node*)malloc(sizeof(Node));
            if (node == NULL) {
                fprintf(stderr, "内存分配失败\n");
                return false;
            }
            node->data = newData;
            node->next = current->next;
            current->next = node;
            return true;
        }
        current = current->next;
    }
    return false; // 未找到指定联系人
}
/*函数功能：*/
bool InsertContactAfter(Node* head, Node* target, Contact data)
{
    Node* node = new Node;//创建一个新的结点
    if (node)
    {
        node->data = data;//数据域赋值
        node->next = target->next;
        target->next = node;
        return true;
    }
}
/*函数功能：在指定联系人的前面插入一个新的联系人
* 函数形参：通讯录链表头指针Node* head，指定联系人地址Node* target，联系人信息Contact data
* 函数返回值：插入成功，返回true，否则返回false，bool类型
*/
bool InsertContactBefore(Node* head, Node* target, Contact data)
{
    Node* pre = SearchPreNode(head, target); //查找指定联系人的前驱结点
    if (pre)
    {
        Node* node = new Node; //=创建一个新的结点
        if (node)
        {
            node->data = data; //数据域赋值
            node->next = target; //指针域赋值
            pre->next = node; //将指定结点的next指针指向新结点
            return true; //插入成功，返回true
        }
    }
    return false; //插入失败，返回false
}
/*函数功能：查找指定联系人的前驱结点
* 函数形参：通讯录链表头指针Node* head，指定联系人地址Node* target，联系人信息Contact data
* 函数返回值：查找成功，返回前驱结点地址，否则返回空，Node*类型
*/
Node* SearchPreNode(Node* head, Node* target)
{
    for (Node* pre = head; pre->next != NULL; pre = pre->next)
    {
        if (pre->next == target)
            return pre; //查找成功，返回前驱结点地址
    }
    return NULL; //查找失败，返回空
}
/*函数功能：删除指定联系人
* 函数形参：通讯录链表头指针Node* head，指定联系人地址Node* target
* 函数返回值：删除成功，返回true，否则返回false，bool类型
*/
bool DeleteContact(Node* head, Node* target)
{
    Node* pre = SearchPreNode(head, target); //查找指定联系人的前驱结点
    if (pre)
    {
        pre->next = target->next; //将前驱结点的next指针指向指定结点的下一个结点
        delete target; //释放指定结点的内存空间
        return true; //删除成功，返回true
    }
    return false; //删除失败，返回false
}
/*函数功能：删除指定联系人的后继
* 函数形参：通讯录链表头指针Node* head，指定联系人地址Node* target
* 函数返回值：删除成功，返回true，否则返回false，bool类型
*/
bool DeleteContactSuccessor(Node* head, Node* target)
{
    Node* pre = SearchPreNode(head, target); //查找指定联系人的前驱结点
    if (pre)
    {
        pre->next = target->next; //将前驱结点的next指针指向指定结点的下一个结点
        delete target; //释放指定结点的内存空间
        return true; //删除成功，返回true
    }
    return false; //删除失败，返回false
}
/*函数功能：打印指定联系人的信息
* 函数形参：通讯录链表头指针Node
* head，指定联系人地址Node* target/
*/