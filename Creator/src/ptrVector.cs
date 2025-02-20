public partial class PtrVector : BufferType {
  //(Int32)length
  //--------------------------------------------------
  public Int32 length {
    get => basicApp_ptrVectorLength(buffer);
  }
  //--------------------------------------------------





  //Inserts the item 'val' at the back of the vector
  //--------------------------------------------------
  public void Insert(IntPtr val) {
    basicApp_ptrVectorInsert(buffer, val);
  }



  //Clears the vector
  //--------------------------------------------------
  public void Clear() {
    basicApp_ptrVectorClear(buffer);
  }



  //Removes an item at index 'at'
  //--------------------------------------------------
  public void Remove(Int64 at) {
    basicApp_ptrVectorRemove(buffer, at);
  }





  //--------------------------------------------------
  //(PtrVector)P[3];
  //(PtrVector)P[4] = (T)6;
  public IntPtr this[Int64 key] {
    get => basicApp_ptrVectorAt(buffer, key);
  }
  //--------------------------------------------------





  public PtrVector(IntPtr ptr) : base(ptr) { }
}