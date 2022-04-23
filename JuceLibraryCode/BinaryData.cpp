/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== Play.svg ==================
static const unsigned char temp_binary_data_0[] =
"<svg width=\"24\" height=\"24\" xmlns=\"http://www.w3.org/2000/svg\" fill-rule=\"evenodd\" clip-rule=\"evenodd\"><path d=\"M23 12l-22 12v-24l22 12zm-21 10.315l18.912-10.315-18.912-10.315v20.63z\"/></svg>";

const char* Play_svg = (const char*) temp_binary_data_0;

//================== Stop.svg ==================
static const unsigned char temp_binary_data_1[] =
"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"24\" height=\"24\" viewBox=\"0 0 24 24\"><path d=\"M18.919 10.431c.24.292.258 1.004-.027 1.284-.252.246-.52.205-1.051.205v-1.71c.503 0 .864-.039 1.078.221zm-5.438.149c-.19.581-.188 2.651 0 3.217.216.6"
"54 1.067.654 1.283 0 .19-.569.19-2.639 0-3.217-.214-.659-1.067-.662-1.283 0zm10.519-3.551v9.941l-7.029 7.03h-9.942l-7.029-7.029v-9.942l7.029-7.029h9.941l7.03 7.029zm-17.09 4.866c-1-.433-1.457-.478-1.457-1.142 0-.793.885-.792 1.119-.437.094.145.141.35"
".141.618h1.088v-.157c0-.268-.044-.498-.131-.689-.286-.633-.918-.823-1.61-.823-.541 0-.966.137-1.275.41-.661.583-.729 2.082.354 2.669.644.35 1.419.396 1.61.91.072.195.107.636-.158.851-.3.244-.837.227-1.066-.067-.162-.206-.149-.533-.149-.795h-1.136c0 ."
"538.017 1.025.414 1.425.553.559 2.118.556 2.812.012.707-.557.861-2.163-.556-2.785zm4.93-2.52h-3.591v.929h1.229v4.693h1.134v-4.693h1.229v-.929zm3.879.709c-.135-.257-.327-.458-.58-.602-.508-.292-1.522-.292-2.031 0-.252.145-.444.345-.578.602-.435.835-.4"
"38 3.367 0 4.205.134.257.326.454.578.591.509.276 1.523.275 2.031 0 .253-.137.445-.333.58-.591.435-.838.434-3.37 0-4.205zm2.971-.709h-1.983v5.623h1.134v-2.244c.638 0 .939.021 1.338-.103 1.509-.466 1.509-3.276-.489-3.276z\"/></svg>";

const char* Stop_svg = (const char*) temp_binary_data_1;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x73db22f9:  numBytes = 191; return Play_svg;
        case 0x6a1588c7:  numBytes = 1219; return Stop_svg;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "Play_svg",
    "Stop_svg"
};

const char* originalFilenames[] =
{
    "Play.svg",
    "Stop.svg"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
