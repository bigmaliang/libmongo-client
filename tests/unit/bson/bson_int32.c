#include "tap.h"
#include "test.h"
#include "bson.h"

#include <string.h>

void
test_bson_int32 (void)
{
  bson *b;
  gint32 i = 1984;

  b = bson_new ();
  ok (bson_append_int32 (b, "i32", i), "bson_append_int32() works");
  bson_finish (b);

  cmp_ok (bson_size (b), "==", 14, "BSON int32 element size check");
  ok (memcmp (bson_data (b),
	      "\016\000\000\000\020\151\063\062\000\300\007\000\000\000",
	      bson_size (b)) == 0,
      "BSON int32 element contents check");

  bson_free (b);
}

RUN_TEST (3, bson_int32);
