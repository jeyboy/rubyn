#include "yaml_lexer_frontend.h"

#include <qiodevice.h>

//Byte0  	 Byte1  	 Byte2  	 Byte3  	 Encoding
//Explicit BOM 	 #x00 	 #x00 	 #xFE 	 #xFF 	 UTF-32BE
//ASCII first character 	 #x00 	 #x00 	 #x00 	 any 	 UTF-32BE
//Explicit BOM 	 #xFF 	 #xFE 	 #x00 	 #x00 	 UTF-32LE
//ASCII first character 	 any 	 #x00 	 #x00 	 #x00 	 UTF-32LE
//Explicit BOM 	 #xFE 	 #xFF 	  	  	 UTF-16BE
//ASCII first character 	 #x00 	 any 	  	  	 UTF-16BE
//Explicit BOM 	 #xFF 	 #xFE 	  	  	 UTF-16LE
//ASCII first character 	 any 	 #x00 	  	  	 UTF-16LE
//Explicit BOM 	 #xEF 	 #xBB 	 #xBF 	  	 UTF-8
//Default 	  	  	  	  	 UTF-8


// http://yaml.org/spec/1.1/
// http://yaml.org/spec/1.2/spec.html
// https://docs.ansible.com/ansible/latest/reference_appendices/YAMLSyntax.html

//%asdasd nnn
//---

//...

LexerFrontendYaml::LexerFrontendYaml(QIODevice * device) {
    while(device -> canReadLine()) {
        QByteArray line = device -> readLine();


    }
}
