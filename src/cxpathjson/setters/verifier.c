
int private_CxpathJson_verifiy_if_insertion_is_possible(CxpathJson *self, cJSON *path_list){

    int path_size = cJSON_GetArraySize(path_list);

    if(path_size == 0){
        char *dumped = cJSON_Print(path_list);
        if(self->raise_runtime_errors){
            CxpathJson_raise_errror(
                    self,
                    CXPATHJSON_ARG_PATH_NOT_VALID_CODE,
                    path_list,
                    PRIVATE_CXPATHJSON_ARG_PATH_NOT_VALID_MESSAGE,
                    dumped
            );
        }
        free(dumped);
        return CXPATHJSON_GENERIC_ERROR;
    }

    cJSON *current_element = self->element;
    for(int i = 0;i <path_size;i++){


        if(!current_element){
            return  CXPATHJSON_OK_CODE;
        }

        cJSON *current_path = cJSON_GetArrayItem(path_list,i);
        bool is_append = private_cxpathjson_path_is_append(current_path);

        bool current_its_object = cJSON_IsObject(current_element);
        bool current_is_an_array = cJSON_IsArray(current_element);
        bool current_its_iterable = cJSON_IsArray(current_element) || current_its_object;

        bool path_must_be_an_object = cJSON_IsString(current_path) && !is_append;
        bool path_must_be_an_array = cJSON_IsNumber(current_path) || is_append;


        if(current_its_iterable == false) {
            if(self->raise_runtime_errors){
                CxpathJson_raise_errror(
                        self,
                        CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_ITERABLE_CODE,
                        path_list,
                        PRIVATE_CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_ITERABLE_MESSAGE
                );
            }
            return  CXPATHJSON_GENERIC_ERROR;
        }

        if(path_must_be_an_object && current_its_object == false){
            if(self->raise_runtime_errors){
                CxpathJson_raise_errror(
                        self,
                        CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_OBJECT_CODE,
                        path_list,
                        PRIVATE_CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_OBJECT_MESSAGE
                );
            }

            return CXPATHJSON_GENERIC_ERROR;

        }

        if(path_must_be_an_array && current_is_an_array == false){
            if(self->raise_runtime_errors){
                CxpathJson_raise_errror(
                        self,
                        CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_ARRAY_CODE,
                        path_list,
                        PRIVATE_CXPATHJSON_MIDDLE_ELEMENT_ITS_NOT_ARRAY_MESSAGE
                );
            }

            return  CXPATHJSON_GENERIC_ERROR;
        }

        if(is_append){
            return  CXPATHJSON_OK_CODE;
        }

        if(current_its_object){
            const char *key = current_path->valuestring;
            current_element = cJSON_GetObjectItem(current_element,key);
        }


        if(current_is_an_array){
            int index = private_cxpathjson_convert_index(
                    current_path->valueint,
                    cJSON_GetArraySize(current_element)
            );
            current_element = cJSON_GetArrayItem(current_element,index);
            if(!current_element){
                //for array explict possitions its required
                if(self->raise_runtime_errors){
                    CxpathJson_raise_errror(
                            self,
                            CXPATHJSON_ELEMENT_PATH_NOT_EXIST_CODE,
                    path_list,
                            PRIVATE_CXPATHJSON_ELEMENT_PATH_NOT_EXIST_MESSAGE
                    );
                }

                return  CXPATHJSON_GENERIC_ERROR;
            }
        }
    }
    return CXPATHJSON_OK_CODE;


}