#include "../../include/littlething.h"

#include <CUnit/Basic.h>

/* ================================================================ */
/* ======================== TEST FUNCTIONS ======================== */
/* ================================================================ */

void LittleThing_init_test(void) {

    LittleThing_init();

    CU_ASSERT_EQUAL(SDL_WasInit(SDL_INIT_VIDEO), SDL_INIT_VIDEO);
    CU_ASSERT_EQUAL(SDL_WasInit(SDL_INIT_EVENTS), SDL_INIT_EVENTS);
}

/* ================================================================ */

int main(int argc, char** argv) {

    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /* Add a suite to the registry */
    if ((pSuite = CU_add_suite("LittleThing_init", NULL, NULL)) == NULL) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (CU_add_test(pSuite, "test of LittleThing_init", LittleThing_init_test) == NULL) {

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