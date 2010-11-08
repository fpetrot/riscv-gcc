/* Contributed by Nicola Pero <nicola.pero@meta-innovation.com>, November 2010.  */
/* { dg-do compile } */

#include <objc/objc.h>

/* Test that if you have a property declared in a class and a
   sub-class, the attributes match.  */

@interface MyRootClass
{
  Class isa;
}
@property (assign) id a;
@property (retain) id b;
@property int c;
@property (nonatomic) int d;
@property int e;
@property int f;
@property int g;
@property (readonly) int h;
@property (readonly,getter=getMe) int i;
@end

@interface MyClass : MyRootClass
@property (assign) id a;
@property (retain) id b;
@property int c;
@property (nonatomic) int d;
@property int e;
@property int f;
@property int g;
@property (readonly) int h;
@property (readonly,getter=getMe) int i;
@end
/* FIXME - there is a problem with the testuite in running the following test.  The compiler generates the messages, but the testsuite still complains.  */
@interface MyClass2 : MyRootClass
/* @property (retain) id a; */         /*  dg-error "assign semantics attributes of property .a. conflict with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 13  */
/* @property (assign) id b; */         /*  dg-error "assign semantics attributes of property .b. conflict with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 14  */
/* @property (nonatomic) int c; */     /*  dg-error ".nonatomic. attribute of property .c. conflicts with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 15  */
/* @property int d; */                 /*  dg-error ".nonatomic. attribute of property .d. conflicts with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 16  */
/* @property (setter=setX:) int e; */  /*  dg-error ".setter. attribute of property .e. conflicts with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 17  */
/* @property (getter=x) int f; */      /*  dg-error ".getter. attribute of property .f. conflicts with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 18  */
/* @property (readonly) int g; */      /*  dg-error ".readonly. attribute of property .g. conflicts with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 19  */
@property (readwrite) int h;     /* Ok */
/* @property (readonly) int i; */      /*  dg-error ".getter. attribute of property .i. conflicts with previous declaration"  */
                                 /*  dg-message "originally specified here" "" { target *-*-* } 21  */
@end
