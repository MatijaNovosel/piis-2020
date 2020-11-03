<template>
  <div class="row no-gutters justify-content-center">
    <group-box title="UML dijagram">
      <div class="col-12">
        <img :src="require('@/assets/clock-state-diagram.png')" />
      </div>
    </group-box>
  </div>
</template>

<script lang="ts">
import { defineComponent, reactive, onMounted } from "vue";

class ClockController {
  incrementHours(): void {
    //
  }
  incrementMinutes(): void {
    //
  }
  incrementSeconds(): void {
    //
  }
  stop(): void {
    //
  }
  doNothing(): void {
    // Do nothing
  }
}

interface ClockState {
  button1(clock: Clock): void;
  button2(clock: Clock): void;
  button1And2(clock: Clock): void;
}

class BlinkHoursClockState implements ClockState {
  button1(clock: Clock): void {
    clock.setBlinkingSeconds();
  }
  button2(clock: Clock): void {
    clock.incrementHours();
  }
  button1And2(clock: Clock): void {
    clock.setStopped();
    clock.stop();
  }
}

class BlinkMinutesClockState implements ClockState {
  button1(clock: Clock): void {
    clock.setBlinkingSeconds();
  }
  button2(clock: Clock): void {
    clock.incrementMinutes();
  }
  button1And2(clock: Clock): void {
    clock.setStopped();
    clock.stop();
  }
}

class BlinkSecondsClockState implements ClockState {
  button1(clock: Clock): void {
    clock.doNothing();
  }
  button2(clock: Clock): void {
    clock.incrementSeconds();
  }
  button1And2(clock: Clock): void {
    clock.setStopped();
    clock.stop();
  }
}

class StoppedClockState implements ClockState {
  button1(clock: Clock): void {
    clock.doNothing();
  }
  button2(clock: Clock): void {
    clock.doNothing();
  }
  button1And2(clock: Clock): void {
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
  isBlinkingHours(): boolean {
    return this._state == this._blinkHoursClockState;
  }

  isBlinkingMinutes(): boolean {
    return this._state == this._blinkMinutesClockState;
  }

  isBlinkingSeconds(): boolean {
    return this._state == this._blinkSecondsClockState;
  }

  isStopped(): boolean {
    return this._state == this._stoppedClockState;
  }

  // State setters
  setBlinkingMinutes(): void {
    this._state = this._blinkMinutesClockState;
  }

  setBlinkingSeconds(): void {
    this._state = this._blinkSecondsClockState;
  }

  setStopped(): void {
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
  incrementHours(): void {
    this._controller?.incrementHours();
  }

  incrementMinutes(): void {
    this._controller?.incrementMinutes();
  }

  incrementSeconds(): void {
    this._controller?.incrementSeconds();
  }

  stop(): void {
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
