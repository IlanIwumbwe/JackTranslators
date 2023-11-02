#include "Lexer.h"
#include "Compiler.h"
#include "Tokeniser.h"
#include "VMtranslator.h"

void vmToASM(std::string& path, VMtranslator& vmt){
    auto vmfiles = GetFilesToParse(path, ".vm");
    auto output_path = GetOutputPath(path, ".asm", "");
    std::ofstream outfile(output_path);

    vmt.Translate(vmfiles, outfile);
    std::cout << "Done translating vm code into asm code in " << output_path << std::endl;
}

int main(int argc, char* argv[]){
    switch(argc){
        case 1:
            std::cout << "Run compiler with arguments: ./Compiler [PATH] [tokens flag(--t)] [final form(--vm or --asm)]" << std::endl;
            return -1;
        default:
            std::string path = argv[1];
            auto file_type = fileType(path);

            if(file_type == "null"){
                std::cout << "Directory is empty." << std::endl;
            } else {
                if (file_type == ".vm"){
                    // call VMTranslator to convert vm code into assembly
                    VMtranslator vmt;

                    if(argc != 2){
                        std::cout << "vm -> asm convertion must have no flags or final form specification" << std::endl;
                    } else {
                        vmToASM(path, vmt);
                    }

                } else if (file_type == ".jack"){

                    auto pair = processCompilerCommand(argc, argv);

                    if(pair.first == ""){
                        return -1;
                    } else {
                        // compiling .jack files
                        auto jackfiles = GetFilesToParse(path, ".jack");

                        Lexer lexer;
                        CompilerXML cpXML; // produces the parse tree of the program
                        Compiler cp; // converts .jack files into .vm files

                        std::string output_path;

                        for(auto path : jackfiles){
                            output_path = "";

                            // tokenise each file
                            lexer.SetFilePath(path);
                            lexer.Lex();
                            
                            if(pair.second){
                                lexer.SaveTokens(path); // save program tokens

                                // save program parse tree
                                lexer.InitialiseCurrToken();
                                output_path = GetOutputPath(path, ".xml", "C");
                                cpXML.Compile(output_path, lexer);
                            }

                            // compile into vm code
                            lexer.InitialiseCurrToken();
                            output_path = GetOutputPath(path, ".vm", "");
                            cp.Compile(output_path, lexer);

                            if(pair.first == "--vm"){
                                return 0;
                            } else {
                                // compile further into asm
                                VMtranslator vmt;
                                vmToASM(path, vmt);
                            }
                        }
                    }

                } else {
                    std::cout << "Invalid file types passed. Only .jack and .vm files allowed" << std::endl;
                }

            }

            return 0;
    }
}
