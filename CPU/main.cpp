//
//  main.cpp
//  CPU
//
//  Created by Эльдар Дамиров on 09.08.2018.
//  Copyright © 2018 Эльдар Дамиров. All rights reserved.
//

#include <iostream>


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <functional>
#include <unordered_map>

#include <time.h>

#include <time.h>
#include <string>
#include <unordered_map>


#include "logsConstants.h"
#include "basicMethods.h"
#include "commandsList.h"

#include "fileIO.h"

#include "stack.h"

#include "compiler.h"







int main() 
    {
    auto myCompiler = Compiler ( "humanCode.txt", "machineCode.txt" );

    return 0;
    }
