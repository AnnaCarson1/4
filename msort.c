#include "sort.h"

/*
  Нийлүүлэн эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
 */
#define CUTOFF 8

/*
  a, b хаяганд хадгалагдсан сурагчдыг нэрээр жиших функц.
  a->name, b->name-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.

*/
int nereer(const Student *a, const Student *b)
{
        int x = strcmp ( a -> name , b -> name ) ;
        if ( x >= 1 ) return -1 ;
        else {
            if ( x == 0 ) return 0 ;
            else return 1 ;
        }
}

/*
  a, b хаяганд хадгалагдсан сурагчдыг насаар нь жиших функц.
  a->age, b->age-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.
*/
int nasaar(const Student *a, const Student *b)
{
        if ( a->age > b->age ) return -1 ;
        else {
            if ( a->age == b->age ) return 0 ;
            else return 1 ;
        }
}

/*
  a, b хаяганд хадгалагдсан сурагчдыг голчоор  нь жиших функц.
  a->gpa, b->gpa-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.
*/
int golchoor(const Student *a, const Student *b)
{
        if ( a->gpa > b->gpa ) return -1 ;
        else {
            if ( a->gpa == b->gpa ) return 0 ;
            else return 1 ;
        }

}


/*
  Оруулан эрэмбэлэх функц.
  Жиших үйлдлийг less функцэн заагчийг ашиглан хийнэ.
  Уг функц нь эрэмбэлэхдээ a хүснэгтийн lo-оос
  hi завсыг л зөвхөн эрэмбэлнэ.
*/
void insertion_sort(Student a[] , int lo , int hi , int (*less)(const Student *, const Student *))
{
        int i , j , l ;
        Student temp ;
        for ( i = lo ; i <= hi ; i ++ ){
            temp = a [ i ] ;
            j = i - 1 ;
            while ( j >= lo && less ( & a [ j ] , & temp ) == -1 ) {
                a [ j + 1 ] = a [ j ] ;
                j -- ;
            }
            a [ j + 1 ] = temp ;
        }
}

/*
  Нийлүүлсэн эрэмбэлэх аргын mege үйлдэл.
  Уг функц нь a хүснэгтэд [lo; mid], [mid+1; hi] завсарт
  эрэмбэлэгдсэн хүснэгтийг нийлүүлэн [lo; hi] завсарт эрэмбэлэгдсэн хүснэгт болгоно.
  aux хүснэгт нь нэмэлтээр ашиглах хүснэгт. Оюутнуудыг хооронд нь жишихдээ less функцэн
  заагчийг ашиглана.
*/
void merge(Student a[],
           Student aux[],
           int lo,
           int mid,
           int hi,
           int (*less)(const Student *, const Student *))
{
        int i = lo ;
        int j = mid + 1 ;
        int l = lo ;
        int k ;
        for ( k = lo ; k <= hi ; k ++ ) {
            aux [ k ] = a [ k ] ;
        }
        while ( i <= mid && j <= hi ) {
            if ( less ( &aux [ i ] , &aux [ j ] ) != -1 ) {
                a [ l ] = aux [ i ] ;
                i ++ ;
            }
            else {
                a [ l ] = aux [ j ] ;
                j ++ ;
            }
            l ++ ;
        }
        while ( i <= mid ) {
            a [ l ] = aux [ i ] ;
            l ++ ;
            i ++ ;
        }
        while ( j <= hi ) {
            a [ l ] = aux [ j ] ;
            l ++ ;
            j ++ ;
        }
}


/*
  Нийлүүлсэн эрэмбэлэх функц.
  hi - lo <= CUTOFF бол оруулан эрэмбэлэх аргыг хэрэглэнэ.
  Жиших үйлдлийг less функцэн заагчийг ашиглан хийнэ.
  Уг функц нь merge, insertion_sort функцүүдийг дуудан ашиглах ёстой.
*/
void mergesort(Student a[],
               Student aux[],
               int lo,
               int hi,
               int (*less)(const Student *, const Student *))
{
        int mid = lo + ( hi - lo ) / 2 ;
        if ( hi - lo <= CUTOFF ) {
            insertion_sort( a , lo , hi , less ) ;
        }
        else {
            mergesort( a , aux , lo , mid , less) ;
            mergesort( a , aux , mid + 1 , hi , less) ;
            merge ( a , aux , lo , mid , hi , less) ;
        }
}
