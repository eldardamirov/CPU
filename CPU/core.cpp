//
//  core.cpp
//  CPU
//
//  Created by Эльдар Дамиров on 18.08.2018.
//  Copyright © 2018 Эльдар Дамиров. All rights reserved.
//


#include "stack.h"
#include "commandsList.h"
#include "basicMethods.h"

#include "fileIO.h"

class Processor
    {
    public:
        Processor() : processorStack ( Stack <double> ( 256, LOW ) ), functionBackMarksStack ( Stack <int> ( 256, LOW ) )
            {
             makeInstructionStack();
//            instructionsArray = new double [ cellQuantity + 2] {};
//                for (int i = cellQuantity + 2; i > 0; i--)
//                    printf ("%d ", instructionsArray[i]);
//             printf ( "SO: %d\n", cellQuantity );
//            
            controlCommandsDoing();
            }
            
            
            
        int controlCommandsDoing()
             {
//             std::cout << "HEY: " << currentMemoryCell << " " << instructionsArraySize << std::endl;

             while ( 1 )
                 {
                 if ( doCommand() == -9 )
                     {
                     return 0;
                     }
                 }
             
             return 0;
             }
             
             
         //////////////////////////////
        //////////////////////////////
        //////////////////////////////
            

            
        
        
        //////////////////////////////
        //////////////////////////////
        //////////////////////////////
        
    
    private:
        Stack <double> processorStack;
        Stack <int> functionBackMarksStack;
        double* ram = new double [ 1024 ] {};
        size_t commandsQuantity = 0;
        int currentMemoryCell = 0;
        int cellQuantity = 0;
        double* instructionsArray = NULL;   // MAKE SOMETHING NORMAL HERE, PLEASE;s 100000000
//        double* instructionsArray = new double [ cellQuantity * 100 ] {};   // MAKE SOMETHING NORMAL HERE, PLEASE;s
        
        
        // REGISTERS
        double* registerArray = new double [ registerQuantity ] {};
        
        
//        double ax = 0.0, bx = 0.0, cx = 0.0, dx = 0.0;
//        double n1 = 0.0, n2 = 0.0, nS = 0.0;
//        double r1 = 0.0, r2 = 0.0, r3 = 0.0, r4 = 0.0;
        
        
        
        
        int makeInstructionStack()
            {
            readFromFile machineCode ( "machineCode.txt" );
            commandsQuantity = machineCode.calculateLinesQuantity();
            
            
            cellQuantity = fromStringToNumber ( machineCode.getTillEndOfLine() );

            instructionsArray = new double [ cellQuantity ] {};

//            cellQuantity = fromStringToNumber ( machineCode.getTillEndOfLine() );
//            printf ( "SO HERE IT IS: %d\n", cellQuantity );

            int currentCellTemp = 0;
            for ( int currentLine = 1; currentLine < commandsQuantity; currentLine++ )
                {
                currentCellTemp = currentCellTemp + parseLine ( machineCode.getTillEndOfLine(), currentCellTemp );
//                parseLine ( machineCode.getTillEndOfLine(), currentCellTemp );
                }
            
//            printf ("GOVNO: %d\n", currentCellTemp);
            
//            for ( int i = 0; i < 64; i++ )
//                {
//                std::cout << instructionsArray [ i ] << " ";
//                }
//            std::cout << "\n";
            return currentCellTemp;
            }
        
        int parseLine ( std::string currentLine, int currentCellTemp )
            {
            int shift = 0;
            std::string currentWord = "";
            size_t lineSize = currentLine.size();
//            printf ( "Parsing: %s, size: %d\n",currentLine.c_str(), lineSize );
            
            for ( int currentCharIndex = 0; currentCharIndex < lineSize; currentCharIndex++ )
                {
                if ( currentLine [ currentCharIndex ] == ' ' )
                    {
                    ///////////////////////////////////////////
                    ///////////////////////////////////////////
                    ///////////////////////////////////////////
                    if ( currentWord != "" )
                        {
                        instructionsArray [ currentCellTemp + shift ] = std::stod ( currentWord );
                        }
                    
                    //////////////////////////////////////////
                    ///////////////////////////////////////////
                    ///////////////////////////////////////////
                    
                    
                    shift++;
//                    printf ( "Parsed new word: %s, adress:%d\n", currentWord.c_str(), ( currentCellTemp + shift ) );
                    currentWord = "";

                    }
                else
                    {
                    currentWord = currentWord + currentLine [ currentCharIndex ];
//                    printf ( "And current word is: %s\n", currentWord.c_str() );
                    }
                }
//                printf ( "!:%s:!\n", currentWord.c_str() );
            if ( currentWord != "" )
                {
                instructionsArray [ currentCellTemp + shift ] = std::stod ( currentWord );
                shift++;
                }
//            shift++;
            
            return shift;
            }
            
        
        
        int doCommand () 
            {
            
//            std::cout << "Current memory cell: " << currentMemoryCell << "\n";
            int commandId = instructionsArray [ currentMemoryCell ];
//            printf ( "\nNow I'm doing command with id %d \n", commandId );
//            printf ( "Current memory cell: %d\n", currentMemoryCell );
//            int operandaModifier = instructionsArray [ currentMemoryCell + 1 ]; //  IMPORTANT: note that operandaModifier current function variable may not contain real command operandaModifier;
            
            switch ( commandId )
                {
                case hlt:
                    return -9; // stop;
                case nullCommand:
                    return nullCommand; // some error occured;
                case out:
                    stackOut();
                    return 2;
                case add:
                    stackAdd();
                    return 2;
                case sub:
                    stackSub();
                    return 2;
                case mul:
                    stackMul();
                    return 2;
                case myDiv:
                    stackDiv();
                    return 2;
                case mySin:
                    stackSin();
                    return 2;
                case myCos:
                    stackCos();
                    return 2;
                case mySqrt:
                    stackSqrt();
                    return 2;
                case myAbs:
                    stackAbs();
                    return 2;
                case myDup:
                    stackDup();
                    return 2;
                case dump:
                    stackDump();
                    return 2;
                case ret:
                    {
//                    printf ( "That is true, I am ret, and current stack size is: %d", functionBackMarksStack.size() );
                    if ( functionBackMarksStack.size() > 0 )
                        {
//                        printf ( "And top element is equal to %d\n", *functionBackMarksStack.top() );
                        currentMemoryCell = *functionBackMarksStack.top(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        functionBackMarksStack.pop();
                        }
                    else
                        {
                        currentMemoryCell = currentMemoryCell + 2;
                        }
                    return 0;
                    }
                case pop:
                    {
                    int operandaModifier = instructionsArray [ currentMemoryCell + 1 ];
                    
                    return popMe ( operandaModifier );
                    }
                case push:
                    {
                    int operandaModifier = instructionsArray [ currentMemoryCell + 1 ];
                    
                    return pushMe ( operandaModifier );
                    }
                case in:
                    {
                    stackIn();
                    return 0;
                    }
                case call:
                    {
                    functionBackMarksStack.push ( ( currentMemoryCell + 2 ) );
                    currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                    return 0;
                    }
                case jmp:
                    {
//                    int cellAdress = instructionsArray [ currentMemoryCell + 1 ];  
                    currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                    
                    return 0;
                    }
                case je:
                    {
                    if ( processorStack.size() >= 2 )
                        {
                        //security checks HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        double first = *processorStack.top();
                        processorStack.pop();
                        double second = *processorStack.top();
                        processorStack.pop();
                        printf ( "VERY IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!: %f, %f\n", first, second );
                        if ( first == second )
                            {
                            currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                            return 0;
                            }
                        }
                        
                    currentMemoryCell = currentMemoryCell + 2;
                    
                    return 0;
                    }
                case jne:
                    {
                    if ( processorStack.size() >= 2 )
                        {
//                       std::cout << "I was here\n";
                        double first = *processorStack.top();
                        processorStack.pop();
                        double second = *processorStack.top();
                        processorStack.pop();
//                       std::cout << first << "  " << second << "\n";
                        if ( first != second )
                            {
//                       std::cout << "And here I was!\n";
                            currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                            return 0;
                            }
                        }
                        
                    currentMemoryCell = currentMemoryCell + 2;
                    
                    return 0;
                    }
                case ja:
                    {
                    if ( processorStack.size() >= 2 )
                        {
                        double first = *processorStack.top();
                        processorStack.pop();
                        double second = *processorStack.top();
                        processorStack.pop();
                        
                        if ( first > second )
                            {
                            currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                            return 0;
                            }
                        }
                        
                    currentMemoryCell = currentMemoryCell + 2;
                    
                    return 0;
                    }
                case jae:
                    {
                    if ( processorStack.size() >= 2 )
                        {
                        double first = *processorStack.top();
                        processorStack.pop();
                        double second = *processorStack.top();
                        processorStack.pop();
                        if ( first >= second )
                            {
                            currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                            return 0;
                            }
                        }
                        
                    currentMemoryCell = currentMemoryCell + 2;
                    
                    return 0;
                    }
                case jb:
                    {
                    if ( processorStack.size() >= 2 )
                        {
                        double first = *processorStack.top();
                        processorStack.pop();
                        double second = *processorStack.top();
                        processorStack.pop();
                        if ( first < second )
                            {
                            currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                            return 0;
                            }
                        }
                    
                    currentMemoryCell = currentMemoryCell + 2;
                    
                    return 0;
                    }
                case jbe:
                    {
                    if ( processorStack.size() >= 2 )
                        {
                        double first = *processorStack.top();
                        processorStack.pop();
                        double second = *processorStack.top();
                        processorStack.pop();
                        if ( first <= second )
                            {
                            currentMemoryCell = instructionsArray [ currentMemoryCell + 1 ] + 1;
                            return 0;
                            }
                        }
                        
                    currentMemoryCell = currentMemoryCell + 2;
                    
                    return 0;
                    }
                default:
                    return -7;
                }
            return 0;
            }
            
        int pushMe ( int operandaModifier )
            {
            if ( operandaModifier == 0 )
                {
                processorStack.push ( ram [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] );
                
                currentMemoryCell = currentMemoryCell + 3;
                return 0;
                }
            
            if ( operandaModifier == 1 )
                {
                processorStack.push ( ram [ ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] ] );
                
                currentMemoryCell = currentMemoryCell + 3;
                return 0;
                }
            
            if ( operandaModifier == 2 )
                {
                processorStack.push ( ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] + ( int ) instructionsArray [ currentMemoryCell + 3 ] ) ] );
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
            
            if ( operandaModifier == 3 )
                {
                processorStack.push ( ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] + ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 3 ] ] ) ] );
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
            
            if ( operandaModifier == 4 )
                {
                processorStack.push ( ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] - ( int ) instructionsArray [ currentMemoryCell + 3 ] ) ] );
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
                
            if ( operandaModifier == 5 )
                {
                processorStack.push ( ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] - ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 3 ] ] ) ] );
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
                
            if ( operandaModifier == 6 )
                {
                processorStack.push ( instructionsArray [ currentMemoryCell + 2 ] );
                
//                std::cout << "DEBUG: " << *processorStack.top() << " AND SIZE IS: " << processorStack.size() << std::endl;
                
                currentMemoryCell = currentMemoryCell + 3;
                return 0;
                }
            
            if ( operandaModifier == 7 )
                {
                processorStack.push ( registerArray [ ( int ) instructionsArray [ ( int ) currentMemoryCell + 2 ] ] );
//                std::cout << "DEBUG: " << *processorStack.top() << " " << registerArray [ ( int ) instructionsArray [ ( int ) currentMemoryCell + 2 ] ] << " AND SIZE IS: " << processorStack.size() << std::endl;
                currentMemoryCell = currentMemoryCell + 3;
                return 0;
                }
            
            
            return -1;
            }
            
        int popMe ( int operandaModifier )
            {
            if ( operandaModifier == 0 )
                {
                int temp = ( int ) instructionsArray [ currentMemoryCell + 2 ];
                ram [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] = *processorStack.top();
                processorStack.pop();
                
                currentMemoryCell = currentMemoryCell + 3;
                return 0;
                }
            
            if ( operandaModifier == 1 )
                {
                ram [ ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] ] = *processorStack.top();
                processorStack.pop();
                
                currentMemoryCell = currentMemoryCell + 3;
                return 0;
                }
            
            if ( operandaModifier == 2 )
                {
                ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] + ( int ) instructionsArray [ currentMemoryCell + 3 ] ) ] = *processorStack.top();
                processorStack.pop();
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
            
            if ( operandaModifier == 3 )
                {
                ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] + ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 3 ] ] ) ] = *processorStack.top();
                processorStack.pop();
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
            
            if ( operandaModifier == 4 )
                {
                ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] - ( int ) instructionsArray [ currentMemoryCell + 3 ] ) ] = *processorStack.top();
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
                
            if ( operandaModifier == 5 )
                {
                ram [ ( int ) ( ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] - ( int ) registerArray [ ( int ) instructionsArray [ currentMemoryCell + 3 ] ] ) ] = *processorStack.top();
                processorStack.pop();
                
                currentMemoryCell = currentMemoryCell + 4;
                return 0;
                }
                
            if ( operandaModifier == -1 )
                {
                processorStack.pop();
                
                currentMemoryCell = currentMemoryCell + 2;
                return 0;
                }
            
            if ( operandaModifier == 7 )
                {
                registerArray [ ( int ) instructionsArray [ currentMemoryCell + 2 ] ] = *processorStack.top();
//                std::cout << " HEYY " << *processorStack.top() << "\n";
                processorStack.pop();
                
                currentMemoryCell = currentMemoryCell + 3;
                return 0;
                }
                

            return -1;
            }
            
        int stackOut()
            {
//            std::cout << "I was here!\n";
            printf ( "%f\n", *processorStack.top() );
//            std::cout << ( double ) *processorStack.top();

            processorStack.pop();
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackAdd()
            {
            double temp = 0;
            
//            std::cout << "I've pushed: " << temp << std::endl;
            
//            std::cout << ">>>>>>>>>>>>>>>>>> DUMP <<<<<<<<<<<<<<<<<<<<\n";
//            std::cout << processorStack.size() << "\n";
//            std::cout << ">>>>>>>>>>>>>>>>>> DUMP <<<<<<<<<<<<<<<<<<<<\n";
            
            temp = temp + *processorStack.top();
//            std::cout << "I've pushed: " << temp << std::endl;
            processorStack.pop();
            temp = temp + *processorStack.top();
//            std::cout << "AHA!: " << *processorStack.top() << std::endl;
            processorStack.pop();
            processorStack.push ( temp );
            
//            std::cout << "I've pushed: " << temp << std::endl;

            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackSub()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            temp = temp - *processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackMul()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            temp = temp * *processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackDiv()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            temp = temp / *processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackSin()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( sin ( temp ) );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackCos()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( cos ( temp ) );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackSqrt()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( sqrt ( temp ) );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackAbs()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( abs ( temp ) );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackDup()
            {
//            std::cout << "I was here! size: " << processorStack.size() << "\n";
            processorStack.push ( *processorStack.top() );
//            std::cout << "Final! size: " << processorStack.size() << "\n";
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackDump()
            {
//            processorStack.dump();
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
            
        int stackPopS()
            {
            processorStack.pop();
            
            return 0;
            }

    
            
        int stackIn()
            {
            double temp = 0.0;
            std::cin >> temp;
            
            processorStack.push ( temp );
            
            currentMemoryCell = currentMemoryCell + 2;
            return 0;
            }
        
    };
