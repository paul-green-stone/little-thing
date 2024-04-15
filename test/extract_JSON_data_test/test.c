#include "../../include/littlething.h"

#include <CUnit/Basic.h>

/* ================================================================ */
/* ======================== TEST FUNCTIONS ======================== */
/* ================================================================ */

void extract_JSON_data_test(void) {

    char* file_content = NULL;

    cJSON* root = NULL;
    cJSON* data = NULL;

    if (read_file("test.json", &file_content) != 0) {
        return ;
    }

    CU_ASSERT_PTR_NOT_NULL(file_content);

    root = cJSON_Parse(file_content);

    extract_JSON_data(root, "name", cJSON_IsString, &data);

    CU_ASSERT_STRING_EQUAL(data->valuestring, "Paul Stone");

    free(file_content);

    cJSON_Delete(root);
}

/* ================================================================ */

int main(int argc, char** argv) {

    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* Add a suite to the registry */
    if ((pSuite = CU_add_suite("extract_JSON_data", NULL, NULL)) == NULL) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (CU_add_test(pSuite, "test of extract_JSON_data", extract_JSON_data_test) == NULL) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    /* ======== */

    return CU_get_error();
}

/* ================================================================ */
