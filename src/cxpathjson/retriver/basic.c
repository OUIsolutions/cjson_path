
cJSON * private_CxpathJson_cJSON_by_cjson_path_list(CxpathJson * self, cJSON *path_list){
    if(CxpathJson_get_error_code(self)){
        return NULL;
    }

    cJSON *current_element = self->element;
    int path_size = cJSON_GetArraySize(path_list);
    for(int i = 0;i <path_size;i++){

        if(!current_element){
            if(self->raise_runtime_errors){
                CxpathJson  *root = private_CxpathJson_get_root(self);
                CxpathJson_raise_errror(
                        root,
                        CXPATHJSON_ELEMENT_PATH_NOT_EXIST_CODE,
                        path_list,
                        PRIVATE_CXPATHJSON_ELEMENT_PATH_NOT_EXIST_MESSAGE
                );
            }

            return  NULL;
        }

        bool current_its_object = cJSON_IsObject(current_element);
        bool current_its_terable = cJSON_IsArray(current_element) || current_its_object;

        if(!current_its_terable){

            if(self->raise_runtime_errors){
                CxpathJson  *root = private_CxpathJson_get_root(self);

                CxpathJson_raise_errror(
                        root,
                        CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_ITERABLE_CODE,
                        path_list,
                        PRIVATE_CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_ITERABLE_MESSAGE
                );
            }

            return  NULL;
        }

        cJSON *current_path = cJSON_GetArrayItem(path_list,i);

        if(cJSON_IsString(current_path) && !current_its_object){
            if(self->raise_runtime_errors){
                CxpathJson  *root = private_CxpathJson_get_root(self);
                CxpathJson_raise_errror(
                        root,
                        CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_OBJECT_CODE,
                        path_list,
                        PRIVATE_CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_OBJECT_MESSAGE
                );
            }
            return  NULL;
        }


        if(cJSON_IsString(current_path)){
            current_element = cJSON_GetObjectItem(current_element,current_path->valuestring);
        }


        if(cJSON_IsNumber(current_path)){
            int index = private_cxpathjson_convert_index(
                    current_path->valueint,
                    cJSON_GetArraySize(current_element));
            current_element = cJSON_GetArrayItem(current_element,index);
        }

    }

    if(!current_element){
        if(self->raise_runtime_errors){
            CxpathJson  *root = private_CxpathJson_get_root(self);
            CxpathJson_raise_errror(
                    root,
                    CXPATHJSON_ELEMENT_PATH_NOT_EXIST_CODE,
                    path_list,
                    PRIVATE_CXPATHJSON_ELEMENT_PATH_NOT_EXIST_MESSAGE
            );
        }

        return  NULL;
    }

    return current_element;
}

cJSON * private_CxpathJson_get_cJSON_by_vargs(CxpathJson * self, const char *format, va_list args){
    if(CxpathJson_get_error_code(self)){
        return NULL;
    }
    char buffer[2000] = {0};
    vsnprintf(buffer, sizeof(buffer), format, args);
    private_cxpathjson_replace_comas(buffer);
    cJSON *parsed_path  = cJSON_Parse(buffer);

    if(private_cxpathjson_validate_path(parsed_path)){
        //we raise here beacause bad formatting its consider a comptime error
        CxpathJson  *root = private_CxpathJson_get_root(self);
        CxpathJson_raise_errror(root,
                                CXPATHJSON_ARG_PATH_NOT_VALID_CODE,
                                NULL,
                                PRIVATE_CXPATHJSON_ARG_PATH_NOT_VALID_MESSAGE,
                                buffer
        );

        cJSON_Delete(parsed_path);
        return  NULL;
    }
    cJSON *result = private_CxpathJson_cJSON_by_cjson_path_list(self, parsed_path);
    cJSON_Delete(parsed_path);
    return result;

}
