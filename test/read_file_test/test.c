#include "../../include/littlething.h"

#include <CUnit/Basic.h>

/* ================================================================ */
/* ======================== TEST FUNCTIONS ======================== */
/* ================================================================ */

void read_file_test(void) {

    char* file_content = NULL;

    if (read_file("test.txt", &file_content) != 0) {
        return ;
    }

    CU_ASSERT_PTR_NOT_NULL(file_content);

    CU_ASSERT_STRING_EQUAL(file_content, "Simple string\n");

    free(file_content);

}

/* ================================================================ */

int main(int argc, char** argv) {

    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* Add a suite to the registry */
    if ((pSuite = CU_add_suite("read_file", NULL, NULL)) == NULL) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (CU_add_test(pSuite, "test of read_file", read_file_test) == NULL) {

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
