func vari<N>(members: N...) {
   for i in members {
      print(i)
   }
}
vari(members:4,3,5)
vari(members:4.5, 3.1, 5.6)
vari(members:"Swift", "Enumerations", "Closures")
