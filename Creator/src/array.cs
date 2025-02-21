public class Array<T> : BufferType where T : struct {
  //(Int64)length
  //--------------------------------------------------
  public Int64 length { get; private set; }
  //--------------------------------------------------



  //
  //--------------------------------------------------
  public Int64 size { get; private set; }


  //(bool)inHouse
  //--------------------------------------------------
  private bool inHouse = false;
  //--------------------------------------------------




  //--------------------------------------------------
  public void CopyFrom(T[] arr) {
    Int64 smallest = length <= arr.Length ? length : arr.Length;
    for (int i = 0; i < smallest; i++)
      this[i] = arr[i];
  }


  //--------------------------------------------------
  //(Array)P[3];
  //(Array)P[2] = (T)10;
  public unsafe T this[Int64 key] {
    get {
      if (key >= length || key < 0)
        throw new ArrayOutOfBoundsException("Cannot retrieve data outside array range");
      return *(T*)(buffer + key * sizeof(T));
    }
    set {
      if (key >= length || key < 0)
        throw new ArrayOutOfBoundsException("Cannot set data outside array range");
      *(T*)(buffer + key * sizeof(T)) = value; 
    }
  }
  //--------------------------------------------------





  public Array(IntPtr ptr, Int64 l, Int64 s) : base(ptr) {
    length = l;
    size = s;
    inHouse = false;
  }

  public Array(Int64 l, Int64 s) : base(ArrayData.basicApp_createArray(132)) {
    length = l;
    size = s;
    inHouse = true;
  }





  ~Array() {
    if (inHouse)
      ArrayData.basicApp_deleteArray(buffer);
  }
}