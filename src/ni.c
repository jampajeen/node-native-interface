#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ni.h"

static napi_value CamCapture(napi_env env, napi_callback_info info)
{
    napi_status status;

    size_t argc = 2;
    napi_value args[2];
    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    assert(status == napi_ok);

    if (argc < 2)
    {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return NULL;
    }

    napi_valuetype valuetype0;
    status = napi_typeof(env, args[0], &valuetype0);
    assert(status == napi_ok);

    napi_valuetype valuetype1;
    status = napi_typeof(env, args[1], &valuetype1);
    assert(status == napi_ok);

    if (valuetype0 != napi_string)
    {
        napi_throw_type_error(env, NULL, "argument1 wrong type");
        return NULL;
    }
    if (valuetype1 != napi_number)
    {
        napi_throw_type_error(env, NULL, "argument2 wrong type");
        return NULL;
    }

    // Convert js value to C types
    size_t str_size = 0;
    napi_get_value_string_utf8(env, args[0], NULL, 0, &str_size);

    char *inputParam0 = (char *)calloc(str_size + 1, sizeof(char));
    size_t str_size_read = 0;
    napi_get_value_string_utf8(env, args[0], inputParam0, str_size + 1, &str_size_read);

    int inputParam1;
    status = napi_get_value_int32(env, args[1], &inputParam1);
    assert(status == napi_ok);

    // Call C/Go lib function
    char *res = Capture(inputParam0, inputParam1);

    // Create JS String and return
    napi_value result;
    napi_create_string_utf8(env, res, strlen(res), &result);

    free(inputParam0);
    return result;
}

#define DECLARE_NAPI_METHOD(name, func)         \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }

napi_value Init(napi_env env, napi_value exports)
{
    napi_status status;
    napi_property_descriptor addDescriptor = DECLARE_NAPI_METHOD("CamCapture", CamCapture);
    status = napi_define_properties(env, exports, 1, &addDescriptor);
    assert(status == napi_ok);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)