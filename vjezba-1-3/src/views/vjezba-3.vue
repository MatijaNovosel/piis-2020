<template>
  <div class="row text-center no-gutters justify-content-center">
    <div class="col-8">
      <div class="row justify-content-center">
        <div class="col-12">
          <group-box title="Simulacija" class="mx-auto">
            <div class="row">
              <div class="col-12">
                <span class="digital-clock-font clock shadow">{{
                  state.time
                }}</span>
              </div>
              <div class="col-12 mt-4">
                <span
                  style="font-size: 14px"
                  class="badge badge-pill badge-primary shadow state-pill"
                  >Stanje: {{ clockState() }}</span
                >
              </div>
            </div>
          </group-box>
        </div>
        <div class="col-12 my-5">
          <group-box title="Akcije" class="mx-auto">
            <button
              @click="action(Action.Button1)"
              type="button"
              class="btn btn-primary shadow"
            >
              Button1
            </button>
            <button
              @click="action(Action.Button2)"
              type="button"
              class="btn btn-primary mx-3 shadow"
            >
              Button2
            </button>
            <button
              @click="action(Action.Button1And2)"
              type="button"
              class="btn btn-primary shadow"
            >
              Button1And2
            </button>
          </group-box>
        </div>
        <div class="col-12 mb-5">
          <group-box title="Dijagram" class="mx-auto">
            <img :src="require('@/assets/clock-state-diagram.png')" />
          </group-box>
        </div>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, reactive, onMounted } from "vue";

enum Action {
  Button1 = 1,
  Button2 = 2,
  Button1And2 = 3
}

interface State {
  clock?: Clock | null;
  clockController?: ClockController | null;
  interval: number;
  offsetHours: number;
  offsetMinutes: number;
  offsetSeconds: number;
  blinking: boolean;
  time: string;
}

class ClockController {
  incrementHours(state: State): void {
    state.offsetHours++;
  }
  incrementMinutes(state: State): void {
    state.offsetMinutes++;
  }
  incrementSeconds(state: State): void {
    state.offsetSeconds++;
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
    clock.setBlinkingMinutes();
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
  private _pageState: State;

  // Checker methods
  isBlinkingHours(): boolean {
    return this._state instanceof BlinkHoursClockState;
  }

  isBlinkingMinutes(): boolean {
    return this._state instanceof BlinkMinutesClockState;
  }

  isBlinkingSeconds(): boolean {
    return this._state instanceof BlinkSecondsClockState;
  }

  isStopped(): boolean {
    return this._state instanceof StoppedClockState;
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
    this._controller?.incrementHours(this._pageState);
  }

  incrementMinutes(): void {
    this._controller?.incrementMinutes(this._pageState);
  }

  incrementSeconds(): void {
    this._controller?.incrementSeconds(this._pageState);
  }

  stop(): void {
    this._controller?.stop();
  }

  doNothing(): void {
    this._controller?.doNothing();
  }

  constructor(action: ClockController, pageState: State) {
    this._controller = action;
    this._pageState = pageState;
    this._state = new BlinkHoursClockState();
  }
}

export default defineComponent({
  name: "vjezba-3",
  setup() {
    const state: State = reactive({
      clock: null,
      clockController: null,
      interval: -1,
      offsetHours: 0,
      offsetMinutes: 0,
      offsetSeconds: 0,
      blinking: false,
      time: "00:00:00"
    });

    function action(act: Action): void {
      switch (act) {
        case Action.Button1: {
          state.clock?.button1();
          break;
        }
        case Action.Button2: {
          state.clock?.button2();
          break;
        }
        case Action.Button1And2: {
          state.clock?.button1And2();
          break;
        }
      }
    }

    function updateTime(): void {
      state.blinking = !state.blinking;
      const date = new Date();

      const hourOverflow = Math.floor(
        (date.getMinutes() + state.offsetMinutes) / 60
      );
      const minutesOverflow = Math.floor(
        (date.getSeconds() + state.offsetSeconds) / 60
      );

      const h = (date.getHours() + state.offsetHours + hourOverflow) % 24;
      const m =
        (date.getMinutes() + state.offsetMinutes + minutesOverflow) % 60;
      const s = (date.getSeconds() + state.offsetMinutes) % 60;

      const hours = h.toString().padStart(2, "0");
      const minutes = m.toString().padStart(2, "0");
      const seconds = s.toString().padStart(2, "0");

      state.time = `${
        state.clock?.isBlinkingHours() && state.blinking ? "  " : hours
      }:${
        state.clock?.isBlinkingMinutes() && state.blinking ? "  " : minutes
      }:${state.clock?.isBlinkingSeconds() && state.blinking ? "  " : seconds}`;
    }

    function clockState(): string {
      if (state.clock?.isBlinkingHours()) {
        return "BLINKANJE SATI";
      } else if (state.clock?.isBlinkingMinutes()) {
        return "BLINKANJE MINUTA";
      } else if (state.clock?.isBlinkingSeconds()) {
        return "BLINKANJE SEKUNDI";
      } else {
        return "ZAUSTAVLJENO BLINKANJE";
      }
    }

    onMounted(() => {
      state.clockController = new ClockController();
      state.clock = new Clock(state.clockController, state);
      state.interval = setInterval(() => {
        updateTime();
      }, 1000);
    });

    return { state, action, Action, clockState };
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

.state-pill {
  background-color: var(--vue-logo-green);
  padding: 10px;
}

.btn {
  border-radius: 6px;
}
</style>