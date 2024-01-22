#pragma once

#include "SP/AST/ProgramNode.h"

namespace MockASTs {

    // -------------- CODE
    /*
    // Procedure p {}
    */
    // -------------- TREE
    /*
    // main
    // └── p
    //     └── StmtList
    */
    std::shared_ptr<ProgramNode> mock0();

    // -------------- CODE
    /*
    // Procedure p {
    //   x = 2;
    //   read y;
    //   print x;
    // }
    */
    // -------------- TREE
    /*
    // main
    // └── p
    //     └── StmtList
    //         ├── Assign
    //         │   ├── Variable (x)
    //         │   └── Constant (2)
    //         ├── Read
    //         │   └── Variable (y)
    //         └── Print
    //             └── Variable (x)
    */
    std::shared_ptr<ProgramNode> mock1();

    // -------------- CODE
    /*
    // Procedure p {
    //1   read x;
    //2   while (x < 0) {
    //3     read x;}
    //
    //4   read y;
    //5   if (y < 0) {
    //6     print y;
    //   } else {
    //7     print x;
    //   }
    // }
    */
    // -------------- TREE
    /*
    // main
    // └── p
    //     └── StmtList
    //         ├── Read
    //         │   └── Variable (x)
    //         ├── WhileThen
    //         │   ├── BinaryExpression (<)
    //         │   │   ├── Variable (x)
    //         │   │   └── Constant (0)
    //         │   └── StmtList
    //         │       └── Read
    //         │           └── Variable (x)
    //         │
    //         ├── Read
    //         │   └── Variable (y)
    //         └── IfThenElse
    //             ├── BinaryExpr (<)
    //             │   ├── Variable (y)
    //             │   └── Constant (0)
    //             ├── StmtList
    //             │   └── Print
    //             │       └── Variable (y)
    //             └── StmtList
    //                 └── Print
    //                     └── Variable (x)
    */
    std::shared_ptr<ProgramNode> mock2();

    // -------------- CODE
    /*
    // Procedure p1 {
    //   x = 2;
    //   read y;
    //   call p2
    //   print x;
    //   call p3;
    // }
    // Procedure p2 {
    //   read y;
    // }
    // Procedure p3 {
    //   call p2;
    // }
    */
    // -------------- TREE
    /*
    //    main
    //    ├── p1
    //    │   └── StmtList
    //    │        ├── Assign
    //    │        │   ├── Variable (x)
    //    │        │   └── Constant (2)
    //    │        ├── Read
    //    │        │   └── Variable (y)
    //    │        ├── Call
    //    │        │   └── Procedure (p2)
    //    │        ├── Print
    //    │        │   └── Variable (x)
    //    │        └── Call
    //    │            └── Procedure (p3)
    //    ├── p2
    //    │   └── StmtList
    //    │       └── Read
    //    │           └── Variable (y)
    //    └── p3
    //        └── StmtList
    //            └── Call
    //                └── Procedure (p2)
    */
    std::shared_ptr<ProgramNode> mock3();

    namespace MultiProcedureCalls {
        // -------------- CODE
        /*
        // Procedure p1 {
        //   x = y;
        // }
        // Procedure p2 {
        //   call p1;
        // }
        // Procedure p3 {
        //   call p2;
        // }
        */
        // -------------- TREE
        /*
        //    main
        //    ├── p1
        //    │   └── StmtList
        //    │        └── Assign
        //    │            ├── Variable (x)
        //    │            └── Variable (y)
        //    ├── p2
        //    │   └── StmtList
        //    │       └── Call
        //    │           └── Procedure (p1)
        //    └── p3
        //        └── StmtList
        //            └── Call
        //                └── Procedure (p2)
        */
        std::shared_ptr<ProgramNode> mock0();

        // -------------- CODE
        /*
        // Procedure p1 {
        //   x = y;
        // }
        // Procedure p2 {
        //   call p1;
        // }
        // Procedure p3 {
        //   call p2;
        // }
        // Procedure p4 {
        //   call p3;
        // }
        // Procedure p5 {
        //   call p4;
        // }
        */
        // -------------- TREE
        /*
        //    main
        //    ├── p1
        //    │   └── StmtList
        //    │        └── Assign
        //    │            ├── Variable (x)
        //    │            └── Variable (y)
        //    ├── p2
        //    │   └── StmtList
        //    │       └── Call
        //    │           └── Procedure (p1)
        //    └── p3
        //        └── StmtList
        //            └── Call
        //                └── Procedure (p2)
        */
        std::shared_ptr<ProgramNode> mock1();

        // Code:
        /*
        Procedure A {
        1	while (1 == 1) {
        2		while (1==1) {
        3			call B;
                }
            }
        }

        Procedure B {
        4	print x
        5   read y
        }

        Procedure C {
        6	while (1==1) {
        7		call A;
            }
        }
        */

        // -------------- TREE
        /*
        main
        ├── Procedure A
        │   └── StmtList
        │       └── While (1 == 1)
        │           └── StmtList
        │               └── While (1 == 1)
        │                   └── StmtList
        │                       └── Call B
        ├── Procedure B
        │   └── StmtList
        │       └── Print x
        │       └── Read y
        └── Procedure C
            └── StmtList
                └── While (1 == 1)
                    └── StmtList
                        └── Call A

        */
        std::shared_ptr<ProgramNode> mock2();

        // Code:
        /*
            Procedure A {
        1        print x;
        2        if (y < 0) {
        3            print y;
        4            call B;
                } else {
        5            while (z == 0) {
        6                print w;
        7                call C;
                    }
                }
            }

        Procedure B {
            8       call D;
        }

        Procedure C {
            9        read i;
        }

        Procedure D {
            10      print m;
            11      call C
        };


        */
        // -------------- TREE
        /*
            main
            ├── A
            │   └── StmtList
            │        ├── Print
            │        │   └── Variable (x)
            │        └── IfThenElse
            │            ├── BinaryExpr (<)
            │            │   ├── Variable (y)
            │            │   └── Constant (0)
            │            ├── StmtList
            │            │   ├── Print
            │            │   │   └── Variable (y)
            │            │   └── Call
            │            │       └── Procedure (p1)
            │            └── StmtList
            │                └── WhileThen
            │                   ├── BinaryExpression (=)
            │                   │   ├── Variable (x)
            │                   │   └── Constant (0)
            │                   └── StmtList
            │                       ├── Print
            │                       │   └── Variable (w)
            │                       └── Call
            │                           └── Procedure (c)
            │
            ├── B
            │   └── StmtList
            │       └── Call
            │           └── Procedure (D)
            ├── C
            │   └── Read
            │       └── Variable (i)
            │
            └── D
                └── StmtList
                    ├── Print
                    │   └── Variable (m)
                    └── Call
                        └── Procedure (C)
    */
        std::shared_ptr<ProgramNode> mock3();
    }

    namespace Expression {
        // -------------- CODE
        /*
        // Procedure p {
        //1   x = 1 + 2
        //2   y = 3 + x
        //3   z = x + y
        // }
        */
        // -------------- TREE
        /*
        // main
        // └── p
        //     └── StmtList
        //         ├── Assign
        //         │   └── Variable (x)
        //         │   └── BinaryExpression (+)
        //         │       └── Constant (1)
        //         │       └── Constant (2)
        //         ├── Assign
        //         │   └── Variable (y)
        //         │   └── BinaryExpression (+)
        //         │       └── Constant (3)
        //         │       └── Variable (x)
        //         └── Assign
        //             └── Variable (z)
        //             └── BinaryExpression (+)
        //                 └── Variable (x)
        //                 └── Variable (y)
        */
        std::shared_ptr<ProgramNode> mock0();
        std::shared_ptr<ProgramNode> mock1();
        std::shared_ptr<ProgramNode> mock2();
        std::shared_ptr<ProgramNode> mock4();
    }
};
