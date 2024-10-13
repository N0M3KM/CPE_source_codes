// 67070501016 Drarun Yookphan
#include <stdio.h>
void test_function()
{
    int a;
    printf("Address of a in the Test Function is %p\n", &a);
}
int main()
{
    printf("//Part 1//\n");
    double num[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double *p = num;
    printf("p is %p\n", p); // แสดงค่า address ของ pointer p
    printf("num is %p\n", num);// แสดงค่า address ของ array num
    printf("Address of num[0] is %p\n", &num[0]); // แสดงค่า address ของข้อมูล index 0 ใน array num
    printf("Address of num[1] is %p\n", &num[1]); // แสดงค่า address ของข้อมูล index 1 ใน array num
    printf("Address of num[2] is %p\n", &num[2]); // แสดงค่า address ของข้อมูล index 2 ใน array num
    // พบว่าตำแหน่ง address ของแต่ละ index มีค่าต่างกัน 8 เนื่องจากแต่ละ index จอง memory เป็นชนิด int ซึ่งคือ 8 bytes
    // และในการแสดงค่าที่ไม่เป็น pointer อย่าง index แต่ละตัวใน array ต้องใช้ & เพื่อระบุตำแหน่ง ทำให้ %p แสดงค่าที่ถูกต้อง
    printf("Value of num[0] is %lf\n", *p);  // แสดงค่า pointer ของ pointer p ซึ่งมีค่าเท่ากับ index 0 ใน array
    printf("Value of num[1] is %lf\n", *(p+1)); // แสดงค่า pointer ของ pointer p ในตำแหน่งถัดไป 1 ตัว ซึ่งมีค่าเท่ากับ index 1 ใน array
    printf("Value of num[2] is %lf\n", *(p+2)); // แสดงค่า pointer ของ pointer p ในตำแหน่งถัดไป 2 ตัว ซึ่งมีค่าเท่ากับ index 2 ใน array
    printf("Value of num[0] is %lf\n", *num); // แสดงค่า pointer ของ pointer num ซึ่งมีค่าเท่ากับ index 0 ใน array
    printf("Value of num[1] is %lf\n", *(num +1)); // แสดงค่า pointer ของ pointer num ซึ่งมีค่าเท่ากับ index 1 ใน array
    printf("Value of num[2] is %lf\n", *(num +2)); // แสดงค่า pointer ของ pointer num ซึ่งมีค่าเท่ากับ index 2 ใน array

    printf("//Part 2//\n");
    int a;
    printf("Address of a in the Main Function is %p\n", &a);
    test_function(); // test_function ได้จอง memory เพิ่มสำหรับตัวแปร a อีกตัวในฟังก์ชัน ซึ่งเป็นคนละตัวกันกับ a ใน main function
    //โดยทันทีที่ test function จบการทำงาน ก็จะคืนหน่วยความจำให้เอง
    int b;
    printf("Address of b in the Main Function is %p\n", &b);

    printf("//Part 3//\n");
    char word[3][5] = {"I", "am", "Yuan"};
    printf("Address of word[0] is %p\n", &word[0]); // แสดงค่า address ของคำแรกใน array word
    printf("Address of word[1] is %p\n", &word[1]); // แสดงค่า address ของคำที่สองใน array word
    printf("Address of word[2] is %p\n", &word[2]); // แสดงค่า address ของคำที่สามใน array word
    printf("Value of word[0] is %s\n", word[0]); // แสดงคำแรกใน array word
    printf("Value of word[1] is %s\n", word[1]); // แสดงคำสองใน array word
    printf("Value of word[2] is %s\n", word[2]); // แสดงคำสามใน array word
    return 0;
}