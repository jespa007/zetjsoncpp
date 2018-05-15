# zetjsoncpp 

ZetJsonCpp allows to load data in json format into C estructures. 

As an example, let's supose we want to load the following json data that is saved in sample.json file,

<pre lang="javascript">
{
    // Default encoding for text
    "encoding" : "UTF-8",
     "plug-ins" : [
        "python",
        "c++",
        "ruby"
        ],
    "indent" : { "length" : 3, "use_space": true }
}
</pre>

List 1.1

To load the code saw on list 1.1 we have to declare the following C estructure,

<pre lang="c++">
typedef struct{
    CParserVarInt32<_CONST_CHAR("length")>  m_length;
    CParserVarBool<_CONST_CHAR("use_space")> m_use_space;
}tIdent;

typedef struct
{
    // Default encoding for text
    CParserVarString<_CONST_CHAR("encoding")>         m_encoding;
    
    // Plug-ins loaded at start-up
    CParserVarArrayString<_CONST_CHAR("plug-ins")>      m_plugins;
        
    // Tab indent size
    CParserVarPropertyGroup<tIdent,_CONST_CHAR("indent")> m_indent;
}tSampleJson;
</pre>

List 1.2

And then we have to write the following code to load the data seen on list 1.1 into the estructure on list 1.2,

<pre lang="c++">
using namespace zetjsoncpp;

int main(int argc, char *argv[]){

    // declare our data var interface.
    CParserVarPropertyGroup<tSampleJson> * data_json;

    // create json-parser
    CParserJson<tSampleJson> * parser = new CParserJson<tSampleJson>();

    // parse our file
    if(parser->evalFile("sample.json")){
        // get data from parser.
        data_json = parser->getData();
  
        // Then you already have all data filled in the struct data_json :)
    }
    
    // deallocates parser
    delete parser;

    // ... and that's all :)
    return 0;
}
</pre>

And then we can manage all data loaded into our C code,

<pre lang="c++">
using namespace zetjsoncpp;

int main(int argc, char *argv[]){

    // declare our data var interface.
    CParserVarPropertyGroup<tSampleJson> * data_json;

    // create json-parser
    CParserJson<tSampleJson> * parser = new CParserJson<tSampleJson>();

    // parse our file
    if(parser->evalFile("sample.json")){
        // get data from parser.
        data_json = parser->getData();

         // Show the values before modifications at screen.
        std::cout << " Before modifications:"<< std::endl;
        std::cout << data_json->cpp2json();       

        // From here we can operate with loaded data in our program using c++ operators
        // put m_use_space to false...
        data_json->m_indent.m_use_space = false;

        // iterate of all m_plugins var and replace with random strings...
        for(unsigned i = 0; i < data_json->m_plugins.size(); i++) {
            data_json->m_plugins[i] = "my_randomstring"+intToString(i+1);
        }
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << " After modifications:"<< std::endl;
               
        // show the modifications at screen (it can be saved in file too)
        std::cout << data_json->cpp2json();

    }
    
    // deallocates parser
    delete parser;

    // that's all :)
    return 0;

}
</pre>


