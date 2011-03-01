#include "tap.h"
#include "test.h"
#include "bson.h"

#include <string.h>

void
test_bson_symbol (void)
{
  bson *b;

  /* Test #1: A single symbol element, with default size. */
  b = bson_new ();
  ok (bson_append_symbol (b, "hello", "world", -1),
      "bson_append_symbol() works");
  bson_finish (b);
  cmp_ok (bson_size (b), "==", 22, "BSON symbol element size check");
  ok (memcmp (bson_data (b),
	      "\026\000\000\000\016\150\145\154\154\157\000\006\000\000\000"
	      "\167\157\162\154\144\000\000",
	      bson_size (b)) == 0,
      "BSON symbol element contents check");
  bson_free (b);

  /* Test #2: A single symbol element, with explicit length. */
  b = bson_new ();
  ok (bson_append_symbol (b, "goodbye",
			  "cruel world, this garbage is gone.",
			  strlen ("cruel world")),
      "bson_append_symbol() with explicit length works");
  bson_finish (b);

  cmp_ok (bson_size (b), "==", 30, "BSON symbol element size check, #2");
  ok (memcmp (bson_data (b),
	      "\036\000\000\000\016\147\157\157\144\142\171\145\000\014\000"
	      "\000\000\143\162\165\145\154\040\167\157\162\154\144\000\000",
	      bson_size (b)) == 0,
      "BSON symbol element contents check, #2");
  bson_free (b);

  /* Test #3: Negative test, passing an invalid length. */
  b = bson_new ();
  ok (bson_append_symbol (b, "hello", "world", -42) == FALSE,
      "bson_append_symbol() fails with an invalid length");
  bson_free (b);
}

RUN_TEST (7, bson_symbol);
