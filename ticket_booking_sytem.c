#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

struct Node
{
  int key;
  struct Node *left;
  struct Node *right;
  char name[100];
  struct node *Key;
  int height;
};

struct node
{
  struct node *prev;
  struct node *next;
  int status;
  int data;
};

struct node *newnd()
{
  struct node *temp1 = (struct node *)malloc(sizeof(struct node));
  temp1->prev = temp1->next = NULL;
  temp1->data = 0;
  temp1->status = 0;
  return temp1;
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

void dd(struct Node *root);

int height(struct Node *N)
{
  if (N == NULL)
    return 0;
  return N->height;
}

struct Node *newNode(int key)
{
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  // char r[10] = {"hi"};
  printf("Enter the name of the movie: ");
  char r[100];
  fflush(stdin);
  // gets(r);
  gets(r);
  strcpy(node->name, r);
  struct node *ty = newnd();
  node->Key = ty;
  return (node);
}

struct Node *rightRotate(struct Node *y)
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct Node *leftRotate(struct Node *x)
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(struct Node *N)
{
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

struct Node *newNNode(int key, char man[])
{
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;

  strcpy(node->name, man);
  struct node *ty = newnd();
  node->Key = ty;
  return (node);
}

struct Node *inser(struct Node *node, int key, char man[])
{

  if (node == NULL)
    return (newNNode(key, man));

  if (key < node->key)
    node->left = inser(node->left, key, man);
  else if (key > node->key)
    node->right = inser(node->right, key, man);
  else
    return node;

  node->height = 1 + max(height(node->left),
                         height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *insertNode(struct Node *node, int key)
{

  if (node == NULL)
    return (newNode(key));

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  node->height = 1 + max(height(node->left),
                         height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *minValueNode(struct Node *node)
{
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

struct Node *deleteNode(struct Node *root, int key)
{

  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else
  {
    if ((root->left == NULL) || (root->right == NULL))
    {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else
        *root = *temp;
      free(temp);
    }
    else
    {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
                         height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0)
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void printPreOrder(struct Node *root)
{
  if (root != NULL)
  {
    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

void postorder(struct Node *root)
{
  if (root != NULL)
  {
    printPreOrder(root->left);
    printPreOrder(root->right);
    printf("%d ", root->key);
  }
}

void dis(struct Node *root)
{
  if (root != NULL)
  {
    dis(root->left);
    printf("\n%d: %s\n\n", root->key, root->name);
    dd(root);

    dis(root->right);
  }
}

void inorder(struct Node *root)
{
  if (root != NULL)
  {
    inorder(root->left);
    printf("%d ", root->key);
    // printf("%s \n", root->name);
    inorder(root->right);
  }
}
struct Node *sear(struct Node *root, int x)
{
  if (root != NULL)
  {
    sear(root->left, x);
    if (root->key == x)
    {
      printf("%d \n", root->key);
      printf("%s \n", root->name);
      struct node *tr = root->Key;
      while (tr->next != (root->Key))
      {

        // printf(" %d ", tr->data);
        tr = tr->next;
      }

      // printf(" %d \n", tr->data);
      return root;
    }
    sear(root->right, x);
  }
}

void red()
{
  printf("\033[1;31m");
}
void green()
{
  printf("\033[1;32m");
}

void yellow()
{
  printf("\033[1;33m");
}
void blue()
{
  printf("\033[1;34m");
}

void purple()
{
  printf("\033[1;35m");
}

void cyan()
{
  printf("\033[1;36m");
}

void white()
{
  printf("\033[1;37m");
}

void reset()
{
  printf("\033[0m");
}

void ct(struct node **h1)
{
  struct node *t1 = (*h1);

  for (int i = 0; i < 100; i++)
  {

    struct node *newnode1 = NULL;
    newnode1 = (struct node *)malloc(sizeof(struct node));
    newnode1->prev = NULL;
    newnode1->next = NULL;
    newnode1->status = 0;
    if ((*h1) == NULL)
    {

      (*h1) = newnode1;
      (*h1)->next = newnode1;
      newnode1->prev = (*h1);
      (t1) = (*h1);
      (*h1)->data = i + 1;
    }
    else
    {
      t1->next = newnode1;
      newnode1->prev = t1;
      newnode1->next = (*h1);
      t1 = newnode1;
      (*h1)->prev = t1;
      t1->data = i + 1;
    }
    //  printf(" %d ",t1->data);
  }
}

void tr(struct Node *root)
{
  if (root != NULL)
  {
    tr(root->left);
    // printf("%d \n", root->key);
    ct(&(root->Key));

    tr(root->right);
  }
}

struct Node *show()
{
  printf("Enter the number of show you want to enter: ");
  int n;
  scanf("%d", &n);
  struct Node *root = NULL;
  for (int i = 0; i < n; i++)
  {
    printf("\nEnter the show number of the movie:  ");
    int g;
    scanf("%d", &g);

    root = insertNode(root, g);
  }
  tr(root);
  return root;
}

void dd(struct Node *root)
{
  int cnt = -1;
  struct node *temp1 = root->Key;
  char r = 'A';
  red();
  printf("\n\t\t1 2 3 4 5 6 7 8 9 10\n\n");
  printf("\t%c\t", r);
  reset();
  ++r;
  for (int i = 1; temp1->next != (root->Key); i++)
  {
    // r--;

    if (i == 66)
    {
      red();
      printf("\n\n\t%c\t", r);
      reset();
      ++r;
      cnt = 0;
      continue;
    }
    else if (i < 66)
    {
      cnt++;
      if (cnt == 10)
      {
        cnt = -1;
        red();
        printf("\n\t%c\t", r);
        reset();
        ++r;
        continue;
      }
      else
      {
        if (temp1->status == 0)
        {
          cyan();
          printf("_ ");
          reset();
        }
        else
        {
          green();
          printf("B ");
          reset();
        }
        temp1 = temp1->next;
      }
    }
    else
    {
      cnt++;
      if (cnt == 5)
      {
        printf("    ");
      }
      else if (cnt == 10)
      {
        cnt = 0;
        red();
        printf("\n\t%c\t", r);
        reset();
        ++r;
      }
      else
      {

        if (temp1->status == 0)
        {
          purple();
          printf("_ ");
          reset();
        }
        else
        {
          green();
          printf("B ");
          reset();
        }
        temp1 = temp1->next;
      }
    }
  }
  yellow();
  printf("\n\n\t----------------------------------\n");
  blue();
  printf("\t\t     SCREEN   \n");
  reset();
}

void book(struct Node *root)
{
  if (root != NULL)
  {
    book(root->left);

    {
      printf("%d ", root->key);
      printf("%s \n", root->name);

      book(root->right);
    }
  }
}

struct Node *adds(struct Node *root)
{
  printf("Enter the show number of the movie:  ");
  int g;
  scanf("%d", &g);
  root = insertNode(root, g);
  tr(root);
  return root;
}

struct Node *addswkey(struct Node *root, int key, char r[])
{

  root = insertNode(root, key);
  tr(root);
  return root;
}

struct Node *bseat(struct Node *root)
{
  int a, b;
  char r;
  printf("Enter the number of seats you want to book: ");
  scanf("%d", &a);
  dd(root);
  for (int v = 0; v < a; v++)
  {
  label:
    fflush(stdin);
    printf("\nEnter the row you want to book: ");
    scanf("%c", &r);
    if (r >= 'a' && r <= 'z')
    {
      r = (char)toupper(r);
    }
    if (r < 'A' && r > 'Z')
    {
      printf("Please Enter Valid Row No.:  \n");
      v--;
      continue;
    }
    printf("Enter the seat number you want to book: ");
    scanf("%d", &b);
    if (b <= 0 && b > 10)
    {
      printf("Please Enter Valid Seat No.:  \n");
      v--;
      continue;
    }
    b--;
    if (r <= 'F')
    {
      int w = r - 'A' + 1;
      int ss = 10 * (w - 1);

      ss += b;
      printf("%d\n", ss);
      struct node *tem = (root->Key);
      int rr = 0;
      while (tem->next != root->Key)
      {
        // printf("%d ", tem->status);
        if (tem->data == ss)
        {
          if (tem->status == 1)
          {
            printf("\nThe Given Seat is Already booked !!\n");
            printf("Please Book another seat :) \n");

            goto label;
          }
          tem->status = 1;
          rr++;
          break;
        }
        tem = tem->next;
      }
      if (tem->data == ss && rr != 0)
      {
        tem->status = 1;
      }

      dd(root);
    }
    else
    {

      if (b == 4 || b == 5)
      {
        printf("Please Enter valid seat number: ");
        v--;
        continue;
      }
      else if (b <= 3)
      {
        b += 2;
      }
      int w = r - 'A' + 1;
      int ss = 8 * (w - 6 - 1);

      ss += b + 60 - 2;
      printf("\n");
      struct node *tem = (root->Key);
      int rr = 0;
      while (tem->next != root->Key)
      {
        // printf("%d ", tem->status);
        if (tem->data == ss)
        {
          if (tem->status == 1)
          {
            printf("\nThe Given Seat is Already booked !!\n");
            printf("Please Book another seat :) \n");

            goto label;
          }
          tem->status = 1;
          rr++;
          break;
        }
        tem = tem->next;
      }
      if (tem->data == ss && rr != 0)
      {
        tem->status = 1;
      }

      dd(root);
    }
  }
}

struct Node *bookseat(struct Node *root)
{
  int n;
  printf("Enter the show number of the movie: ");

  scanf("%d", &n);
  struct Node *sn = sear(root, n);
  bseat(sn);
  // return sn;
}

struct Node invoice(struct Node *root)
{

  printf("Enter your full Name: ");
  char name[20];
  fflush(stdin);
  scanf("%s", name);

  char pn[20];
  printf("Enter your phone Number: ");
  fflush(stdin);
  scanf("%s", pn);
}

struct Node *Ffile(struct Node *root)
{

  FILE *ptr;

  ptr = fopen("AVLtr.txt", "r");
  if (NULL == ptr)
  {
    printf("File can't be opened! \n");
    // return;
  }

  printf("Content of this file are : \n");
  char ch[100], num[10];
  while (fscanf(ptr, "%s\n", ch) != EOF)
  {

    int r = ch[1] - '0';
    r += ((ch[0] - '0') * 10);

    fscanf(ptr, "%s\n", ch);

    printf("%d %s\n", r, ch);

    root = inser(root, r, ch);
  }

  fclose(ptr);
  tr(root);

  return root;
}

void clse()
{
  yellow();
  printf("\nThank You !!\n");
  printf("Do visit again :)\n");
  reset();
  exit(0);
}

void welcome()
{
 
}

int main()
{

  system("CLS");
  welcome();

  printf("\n*********************************************************************************************\n");
  white();
  printf("\n\t\t\tWelcome to the Movie Ticket Booking System !!\n");
  reset();
  struct Node *root = NULL;
  while (1)
  {

    printf("\n=============================================================================================\n");
    printf("Enter the given number: \n");
    printf("1: Create Show\n");
    printf("2: Add Show\n");
    printf("3: Delete Show\n");
    printf("4: Show the seats of a particular show!\n");
    printf("5: Book Seats!\n");
    printf("6: Show all seats!\n");
    printf("7. To get diferent orders of the AVL Tree!\n");
    // printf("9. To Read data from a file!\n");
    printf("8: Exit!\n");
    int n;
    scanf("%d", &n);
    int x;

    switch (n)
    {
    case 1:
      root = show();
      break;
    case 2:
      root = adds(root);
      printf("\n The show is added successfully !!\n");
      break;
    case 3:
      printf("Enter the show number to delete: ");
      scanf("%d", &x);
      root = deleteNode(root, x);
      printf("\n The required show is deleted!! \n");
      break;
    case 4:
      printf("Enter the show number you want to see! ");
      scanf("%d", &x);
      struct Node *w = sear(root, x);
      dd(w);
      break;
    case 5:
      // dd(root->right);
      book(root);
      bookseat(root);
      printf("\nThe booking is confirmed successfully!!\n");
      break;
    case 8:
      clse();
      break;
    case 7:
      printf("\nThe inorder of the Tree is: ");
      inorder(root);
      printf("\nThe Preorder of the Tree is: ");
      printPreOrder(root);
      printf("\nThe Postorder of the Tree is: ");
      postorder(root);
      break;

    case 6:
      dis(root);
      break;
    case 9:
      root = Ffile(root);
      break;
    default:
      printf("Please Enter a valid number !!");
    }
  }

  return 0;
}
