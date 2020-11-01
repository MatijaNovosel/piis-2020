class Automat<Input, Output> {
  private inVal?: Input | null;
  private outVal?: Output |null;
  Automat() {
    this.inVal = null;
    this.outVal = null;
  }
}