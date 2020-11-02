<template>
  <div class="row text-center no-gutters justify-content-center">
    <div class="col-5">
      <div class="row justify-content-center">
        <div class="col-12">
          <group-box title="Simulacija" class="mx-auto" style="width: 95%">
            <div class="row">
              <div class="col-12">
                <span class="digital-clock-font clock shadow">{{
                  state.clock && state.clock.time
                }}</span>
              </div>
              <div class="col-12 mt-4">
                <span
                  style="font-size: 14px"
                  class="badge badge-pill badge-primary shadow state-pill"
                  >Stanje: {{ state.clockStateComputed }}</span
                >
              </div>
            </div>
          </group-box>
        </div>
        <div class="col-12 my-5">
          <group-box title="Ulazi" class="mx-auto" style="width: 95%">
            <button
              @click="inputBtn(Button.Button1)"
              type="button"
              class="btn btn-primary shadow"
            >
              Button1
            </button>
            <button
              @click="inputBtn(Button.Button2)"
              type="button"
              class="btn btn-primary mx-3 shadow"
            >
              Button2
            </button>
            <button
              @click="inputBtn(Button.Button1And2)"
              type="button"
              class="btn btn-primary shadow"
            >
              Button1And2
            </button>
          </group-box>
        </div>
        <div class="col-12 mb-5">
          <group-box
            title="Dijagram"
            class="mx-auto"
            style="width: 95%"
            v-if="state.clock"
          >
            <img :src="getImg(state.clock.state)" />
          </group-box>
        </div>
      </div>
    </div>
    <div class="col-5">
      <group-box title="Povijest ulaza i stanja" style="width: 95%">
        <span v-if="state.history.length == 0"
          >Nije pronađen ni jedan zapis!</span
        >
        <div v-else>
          <table class="table table-striped">
            <thead>
              <tr>
                <th scope="col">t</th>
                <th scope="col">Ulaz</th>
                <th scope="col">Stanje</th>
                <th scope="col">Izlaz</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(item, i) in state.history" :key="i">
                <th scope="row">{{ i }}</th>
                <td>{{ formatButton(item.input) }}</td>
                <td>{{ item.state }}</td>
                <td>{{ item.output || "null" }}</td>
              </tr>
            </tbody>
          </table>
        </div>
      </group-box>
    </div>
  </div>
</template>

<script lang="ts">
import {
  defineComponent,
  onMounted,
  reactive,
  computed,
  onUnmounted
} from "vue";

interface Output<InVal, State, OutVal> {
  in: InVal;
  state: State;
  out: OutVal;
}

abstract class Automat<State, InValue> {
  protected _state?: State;
  abstract result(
    state?: State,
    inVal?: InValue
  ): Output<number, State, number> | null;
  step(inVal: InValue): Output<number, State, number> | null {
    const output: Output<number, State, number> | null = this.result(
      this._state,
      inVal
    );
    this._state = output?.state;
    return output;
  }
  constructor(startState: State) {
    this._state = startState;
  }
}

enum Button {
  Button1 = 1,
  Button2 = 2,
  Button1And2 = 3
}

enum ClockState {
  BlinkHours = 1,
  BlinkMinutes = 2,
  BlinkSeconds = 3,
  Stopped = 4
}

class Clock extends Automat<ClockState, Button> {
  private _currentTime?: string;
  private _currentTimeNoBlinking?: string;
  private _hoursOffset: number;
  private _minutesOffset: number;
  private _secondsOffset: number;
  private _blinking: boolean;

  updateTime(): void {
    this._blinking = !this._blinking;
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

    const hours = h.toString().padStart(2, "0");
    const minutes = m.toString().padStart(2, "0");
    const seconds = s.toString().padStart(2, "0");

    this._currentTimeNoBlinking = `${hours}:${minutes}:${seconds}`;

    this._currentTime = `${
      this._state == ClockState.BlinkHours && this._blinking ? "  " : hours
    }:${
      this._state == ClockState.BlinkMinutes && this._blinking ? "  " : minutes
    }:${
      this._state == ClockState.BlinkSeconds && this._blinking ? "  " : seconds
    }`;
  }

  result(
    state?: ClockState,
    inVal?: Button
  ): Output<number, ClockState, number> | null {
    const res: Output<number, ClockState, number> = {
      in: inVal || -1,
      state: this._state || ClockState.BlinkHours,
      out: -1
    };

    switch (inVal) {
      case Button.Button1: {
        switch (state) {
          case ClockState.BlinkHours: {
            res.state = ClockState.BlinkMinutes;
            break;
          }
          case ClockState.BlinkMinutes: {
            res.state = ClockState.BlinkSeconds;
            break;
          }
        }
        break;
      }
      case Button.Button2: {
        switch (state) {
          case ClockState.BlinkHours: {
            this._hoursOffset++;
            break;
          }
          case ClockState.BlinkMinutes: {
            this._minutesOffset++;
            break;
          }
          case ClockState.BlinkSeconds: {
            this._secondsOffset++;
            break;
          }
        }
        break;
      }
      case Button.Button1And2: {
        res.state = ClockState.Stopped;
        break;
      }
    }

    return res;
  }

  constructor() {
    super(ClockState.BlinkHours);
    this._hoursOffset = this._minutesOffset = this._secondsOffset = 0;
    this._blinking = false;
    this._currentTime = "00:00:00";
  }

  get time() {
    return this._currentTime;
  }

  get timeNoBlink() {
    return this._currentTimeNoBlinking;
  }

  get state() {
    return this._state;
  }
}

interface HistoryItem {
  state?: string | null;
  input?: string | null;
  output?: string | null;
}

interface State {
  clock?: Clock | null;
  interval: number;
  history: Array<HistoryItem>;
  clockStateComputed: string | undefined;
}

export default defineComponent({
  name: "vjezba-1-sat",
  setup() {
    const state: State = reactive({
      clock: null,
      interval: -1,
      history: [],
      clockStateComputed: computed(() => {
        if (state.clock) {
          switch (state.clock.state) {
            case ClockState.Stopped:
              return "ZAUSTAVLJENO BLINKANJE";
            case ClockState.BlinkHours:
              return "BLINKANJE SATI";
            case ClockState.BlinkMinutes:
              return "BLINKANJE MINUTA";
            case ClockState.BlinkSeconds:
              return "BLINKANJE SEKUNDI";
          }
        }
      })
    });

    onMounted(() => {
      state.clock = new Clock();
      state.interval = setInterval(() => {
        state.clock?.updateTime();
      }, 1000);
      state.history.push({
        state: "BLINKANJE SATI",
        input: null,
        output: state.clock.time
      });
    });

    onUnmounted(() => {
      clearInterval(state.interval);
    });

    function inputBtn(inVal: Button): void {
      const output = state?.clock?.step(inVal);
      state.history.push({
        state: state.clockStateComputed,
        input: output?.in.toString(),
        output: state.clock?.timeNoBlink
      });
    }

    function getImg(state: ClockState): __WebpackModuleApi.RequireContext {
      const images = require.context("../assets/clock", false, /\.png$/);
      return images("./clock-diagram-" + state + ".png");
    }

    function formatButton(btn: Button): string {
      if (btn == Button.Button1) {
        return "Button1";
      } else if (btn == Button.Button2) {
        return "Button2";
      } else if (btn == Button.Button1And2) {
        return "Button1And2";
      } else {
        return "null";
      }
    }

    return {
      state,
      getImg,
      inputBtn,
      Button,
      formatButton
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
.state-pill {
  background-color: var(--vue-logo-green);
  padding: 10px;
}
.btn {
  border-radius: 6px;
}
</style>