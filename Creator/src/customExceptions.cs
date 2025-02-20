public class ArrayOutOfBoundsException : Exception {
  public ArrayOutOfBoundsException() : base() { }
  public ArrayOutOfBoundsException(string message) : base(message) { }
  public ArrayOutOfBoundsException(string message, Exception inner) : base(message, inner) { }
}