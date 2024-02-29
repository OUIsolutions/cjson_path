

typedef struct {


    CxpathJson * (*new_from_cJSON)(cJSON *element);
    CxpathJson * (*newJsonObject)(void);
    CxpathJson * (*newJsonArray)(void);
    CxpathJson * (*new_from_string)( const char *data);
    CxpathJson * (*new_from_file)(const char *path);
    void (*free)(CxpathJson * self);

    cJSON * (*get_cJSON)(CxpathJson * self, const char *format, ...);
    const char * (*get_str)(CxpathJson * self, const char *format, ...);
    double (*get_double)(CxpathJson * self, const char *format, ...);
    int (*get_int)(CxpathJson * self, const char *format, ...);
    bool (*get_bool)(CxpathJson * self, const char *format, ...);
    int (*size)(CxpathJson * self, const char *format, ...);

    void (*set_cjson)(CxpathJson *self, cJSON *value, const char *format, ...);
    void (*set_str)(CxpathJson *self, const char *value, const char *format, ...);
    void (*set_double)(CxpathJson *self, double value, const char *format, ...);
    void (*set_long)(CxpathJson *self, long value, const char *format, ...);
    void (*set_bool)(CxpathJson *self, bool value, const char *format, ...);


    CxpathJsonErrorNamespace errors;

}CxpathJsonNamespace;

CxpathJsonNamespace newCxpathJsonNamespace();