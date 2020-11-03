<template>
  <div class="row text-center no-gutters">
    <div class="col-12 mt-5">
      <img :src="require('@/assets/elevator/elevator-diagram-empty.png')" />
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, reactive, onMounted } from "vue";

class ClockController {
  incrementHours() {
    //
  }
  incrementMinutes() {
    //
  }
  incrementSeconds() {
    //
  }
  stop() {
    //
  }
  doNothing() {
    // Do nothing
  }
}

interface ClockState {
  button1(clock: Clock): void;
  button2(clock: Clock): void;
  button1And2(clock: Clock): void;
}

class BlinkHoursClockState implements ClockState {
  button1(clock: Clock) {
    clock.setBlinkingSeconds();
  }
  button2(clock: Clock) {
    clock.incrementHours();
  }
  button1And2(clock: Clock) {
    clock.setStopped();
    clock.stop();
  }
}

class BlinkMinutesClockState implements ClockState {
  button1(clock: Clock) {
    clock.setBlinkingSeconds();
  }
  button2(clock: Clock) {
    clock.incrementMinutes();
  }
  button1And2(clock: Clock) {
    clock.setStopped();
    clock.stop();
  }
}

class BlinkSecondsClockState implements ClockState {
  button1(clock: Clock) {
    clock.doNothing();
  }
  button2(clock: Clock) {
    clock.incrementSeconds();
  }
  button1And2(clock: Clock) {
    clock.setStopped();
    clock.stop();
  }
}

class StoppedClockState implements ClockState {
  button1(clock: Clock) {
    clock.doNothing();
  }
  button2(clock: Clock) {
    clock.doNothing();
  }
  button1And2(clock: Clock) {
    clock.doNothing();
  }
}

class Clock {
  private _blinkHoursClockState?: BlinkHoursClockState | null = new BlinkHoursClockState();
  private _blinkMinutesClockState?: BlinkMinutesClockState | null = new BlinkMinutesClockState();
  private _blinkSecondsClockState?: BlinkSecondsClockState | null = new BlinkSecondsClockState();
  private _stoppedClockState?: StoppedClockState | null = new StoppedClockState();

  private _controller?: ClockController | null;
  private _state?: ClockState | null;

  // Checker methods
  isBlinkingHours() {
    return this._state == this._blinkHoursClockState;
  }

  isBlinkingMinutes() {
    return this._state == this._blinkMinutesClockState;
  }

  isBlinkingSeconds() {
    return this._state == this._blinkSecondsClockState;
  }

  isStopped() {
    return this._state == this._stoppedClockState;
  }

  // State setters
  setBlinkingMinutes() {
    this._state = this._blinkMinutesClockState;
  }

  setBlinkingSeconds() {
    this._state = this._blinkSecondsClockState;
  }

  setStopped() {
    this._state = this._stoppedClockState;
  }

  // Inputs
  button1(): void {
    this._state?.button1(this);
  }

  button2(): void {
    this._state?.button2(this);
  }

  button1And2(): void {
    this._state?.button1And2(this);
  }

  // Actions
  incrementHours() {
    this._controller?.incrementHours();
  }

  incrementMinutes() {
    this._controller?.incrementMinutes();
  }

  incrementSeconds() {
    this._controller?.incrementSeconds();
  }

  stop() {
    this._controller?.stop();
  }

  doNothing(): void {
    this._controller?.doNothing();
  }

  constructor(action: ClockController) {
    this._controller = action;
    this._state = new BlinkHoursClockState();
  }
}

interface State {
  clock?: Clock | null;
  clockController?: ClockController | null;
  interval: number;
}

export default defineComponent({
  name: "vjezba-3",
  setup() {
    const state: State = reactive({
      clock: null,
      clockController: null,
      interval: -1
    });

    onMounted(() => {
      state.clockController = new ClockController();
      state.clock = new Clock(state.clockController);
    });

    return { state };
  }
});
</script>
