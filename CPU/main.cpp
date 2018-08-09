//
//  main.cpp
//  CPU
//
//  Created by Эльдар Дамиров on 09.08.2018.
//  Copyright © 2018 Эльдар Дамиров. All rights reserved.
//

#include <iostream>
#include "compiler.h"

int main() 
    {
    auto myCompiler = Compiler ( "humanCode.txt", "machineCode.txt" );

    return 0;
    }
