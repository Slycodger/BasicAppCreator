public partial class Array<T> : BufferType where T : struct {
  //(Int64)length
  //--------------------------------------------------
  public Int64 length { get; private set; }
  //--------------------------------------------------





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





  public Array(IntPtr ptr, Int64 l) : base(ptr) {
    length = l;
  }
}