<template>
  <div class="row text-center no-gutters justify-content-center">
    <div class="col-12">
      <span
        style="font-size: 20px"
        class="badge badge-pill badge-primary shadow"
        >Vježba 1 - Sat</span
      >
    </div>
    <div class="col-12 mt-5">
      <group-box title="Simulacija" class="mx-auto" style="width: 500px">
        <span class="digital-clock-font clock shadow" v-if="state.clock">{{
          state.clock.time
        }}</span>
      </group-box>
    </div>
    <div class="col-12 my-5">
      <group-box title="Ulazi" class="mx-auto" style="width: 500px">
        <button type="button" class="btn btn-primary">Increment hours</button>
        <button type="button" class="btn btn-primary mx-3">
          Increment minutes
        </button>
        <button type="button" class="btn btn-primary">Increment seconds</button>
      </group-box>
    </div>
    <div class="col-12 mb-5">
      <group-box title="Dijagram" class="mx-auto" style="width: 500px">
        <img :src="require('../assets/clock-diagram.png')" />
      </group-box>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, onMounted, reactive } from "vue";

interface Output<InVal, State, OutVal> {
  in: InVal;
  state: State;
  out: OutVal;
}

class Automat<State, InValue> {
  private _state?: State;
  // eslint-disable-next-line
  result(state?: State, inVal?: InValue): Output<number, State, number> | null {
    return null;
  }
  step(inVal: InValue): Output<number, State, number> | null {
    const output: Output<number, State, number> | null = this.result(
      this._state,
      inVal
    );
    this._state = output?.state;
    return output;
  }
}

enum Button {
  Button1,
  Button2,
  Button1And2
}

enum Status {
  Stopped,
  BlinkHours,
  BlinkMinutes,
  BlinkSeconds
}

class Clock extends Automat<Status, Button> {
  private _currentTime?: string;
  private _hoursOffset: number;
  private _minutesOffset: number;
  private _secondsOffset: number;
  updateTime(): void {
    const date = new Date();

    const hourOverflow = Math.floor(
      (date.getMinutes() + this._minutesOffset) / 60
    );
    const minutesOverflow = Math.floor(
      (date.getSeconds() + this._secondsOffset) / 60
    );

    const h = (date.getHours() + this._hoursOffset + hourOverflow) % 24;
    const m = (date.getMinutes() + this._minutesOffset + minutesOverflow) % 60;
    const s = (date.getSeconds() + this._minutesOffset) % 60;

    this._currentTime = `${h
      .toString()
      .padStart(2, "0")}:${m
      .toString()
      .padStart(2, "0")}:${s.toString().padStart(2, "0")}`;
  }
  constructor() {
    super();
    this._hoursOffset = this._minutesOffset = this._secondsOffset = 0;
  }
  get time() {
    return this._currentTime;
  }
}

interface State {
  clock?: Clock | null;
}

export default defineComponent({
  name: "vjezba-1",
  setup() {
    const state: State = reactive({
      clock: null
    });

    onMounted(() => {
      state.clock = new Clock();
      setInterval(() => {
        state.clock?.updateTime();
      }, 1000);
    });

    return {
      state
    };
  }
});
</script>

<style scoped>
.clock {
  font-size: 25px;
  background-color: black;
  color: hotpink;
  padding: 12px;
  border-radius: 10px;
  width: 200px;
  display: block;
  margin: 0 auto;
}
</style>