
;; Function main (main, funcdef_no=0, decl_uid=2313, cgraph_uid=1, symbol_order=0)

main ()
{
  int i;
  int x;
  int y;
  int D.2322;

  y = 0;
  x = 10;
  i = 0;
  goto <D.2319>;
  <D.2318>:
  y = y + 1;
  i = i + 1;
  <D.2319>:
  if (i < x) goto <D.2318>; else goto <D.2320>;
  <D.2320>:
  printf ("Value is %d\n", y);
  D.2322 = 0;
  goto <D.2323>;
  D.2322 = 0;
  goto <D.2323>;
  <D.2323>:
  return D.2322;
}


