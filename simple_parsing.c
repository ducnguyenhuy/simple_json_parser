#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSON_FILE   "example.json"

char *read_json(char *file_name)
{
    FILE *file;
    file = fopen(JSON_FILE, "r");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("File could not be opened.\n");
        return NULL;
    }

    // Read and print data from the file using fgets
    char *buffer; // Buffer to store the read data
    buffer = malloc(256);

    fgets(buffer, 256, file);

    // Close the file when done
    fclose(file);

    return buffer;
}

int parse_string_value(const char *input_json, const char *input_key ,char **output_value)
{
    int max_cout = 0;
    char *begin = NULL;
    char *end = NULL;
    char spec_ch[] = "\"";

    begin = strstr(input_json, input_key);

    if(begin == NULL)
        return -1;
    
    begin += strlen(input_key);

    while ((*begin == '"') || (*begin == ' ') || (*begin ==':') || max_cout == 10)
    {
        begin++;
        max_cout++;
    }
    
    end = strstr(begin, spec_ch);

    memcpy(*output_value, begin, (end - begin));

    return 0;
}

int main() {
    char *output_val = NULL;
    output_val = malloc(100);

    char *json_str = read_json(JSON_FILE);
    char key[] = "name";
    parse_string_value(json_str, key, &output_val);

    printf("%s\n", output_val);

    free(json_str);
    free(output_val);
    return 0;
}
