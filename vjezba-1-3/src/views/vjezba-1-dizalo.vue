<template>
  <div class="row text-center no-gutters justify-content-center">
    <div class="col-5">
      <div class="row justify-content-center">
        <div class="col-12">
          <group-box
            title="Simulacija"
            class="mx-auto"
            style="width: 95%"
            v-if="state.elevator"
          >
            <span
              style="font-size: 14px"
              class="badge badge-pill badge-primary shadow state-pill"
              >Stanje: {{ state.elevatorStateComputed }}</span
            >
          </group-box>
        </div>
        <div class="col-12 my-5">
          <group-box title="Ulazi" class="mx-auto" style="width: 95%">
            <button
              @click="inputBtn(Button.a)"
              type="button"
              class="btn btn-primary shadow"
            >
              a
            </button>
            <button
              @click="inputBtn(Button.b)"
              type="button"
              class="btn btn-primary mx-3 shadow"
            >
              b
            </button>
            <button
              @click="inputBtn(Button.c)"
              type="button"
              class="btn btn-primary shadow"
            >
              c
            </button>
            <button
              @click="inputBtn(Button.d)"
              type="button"
              class="btn btn-primary shadow mx-3"
            >
              d
            </button>
            <button
              @click="inputBtn(Button.e)"
              type="button"
              class="btn btn-primary shadow"
            >
              e
            </button>
            <button
              @click="inputBtn(Button.f)"
              type="button"
              class="btn btn-primary shadow ml-3"
            >
              f
            </button>
          </group-box>
        </div>
        <div class="col-12 mb-5">
          <group-box
            title="Dijagram"
            class="mx-auto"
            style="width: 95%"
            v-if="state.elevator"
          >
            <img :src="getImg(state.elevator.state)" />
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
import { defineComponent, onMounted, reactive, computed } from "vue";

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
  a = 1,
  b,
  c,
  d,
  e,
  f
}

enum ElevatorState {
  Standby = 1,
  Waiting1 = 2,
  ClosingDoor = 3,
  Moving = 4,
  Waiting2 = 5,
  OpeningDoor = 6,
  Terminated = 7
}

class Elevator extends Automat<ElevatorState, Button> {
  result(
    state?: ElevatorState,
    inVal?: Button
  ): Output<number, ElevatorState, number> | null {
    const res: Output<number, ElevatorState, number> = {
      in: inVal || -1,
      state: this._state || ElevatorState.Standby,
      out: -1
    };

    const currentState: ElevatorState = this._state || ElevatorState.Standby;

    switch (inVal) {
      case Button.a: {
        if (currentState == ElevatorState.Standby)
          res.state = ElevatorState.Waiting1;
        if (currentState == ElevatorState.Moving)
          res.state = ElevatorState.Waiting2;
        break;
      }
      case Button.b: {
        if ([ElevatorState.Waiting1].includes(currentState))
          res.state = ElevatorState.ClosingDoor;
        break;
      }
      case Button.c: {
        if ([ElevatorState.ClosingDoor].includes(currentState))
          res.state = ElevatorState.Moving;
        break;
      }
      case Button.d: {
        if ([ElevatorState.Waiting2].includes(currentState))
          res.state = ElevatorState.OpeningDoor;
        break;
      }
      case Button.e: {
        if ([ElevatorState.OpeningDoor].includes(currentState))
          res.state = ElevatorState.Standby;
        break;
      }
      case Button.f: {
        if ([ElevatorState.Standby].includes(currentState))
          res.state = ElevatorState.Terminated;
        break;
      }
    }

    return res;
  }

  constructor() {
    super(ElevatorState.Standby);
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
  elevator?: Elevator | null;
  history: Array<HistoryItem>;
  elevatorStateComputed: string | undefined;
}

export default defineComponent({
  name: "vjezba-1-dizalo",
  setup() {
    const state: State = reactive({
      elevator: null,
      history: [],
      elevatorStateComputed: computed(() => {
        if (state.elevator) {
          switch (state.elevator.state) {
            case ElevatorState.Waiting1:
              return "WAITING";
            case ElevatorState.Standby:
              return "STANDBY";
            case ElevatorState.OpeningDoor:
              return "OPENING DOOR";
            case ElevatorState.ClosingDoor:
              return "CLOSING DOOR";
            case ElevatorState.Moving:
              return "MOVING";
            case ElevatorState.Terminated:
              return "TERMINATED";
            case ElevatorState.Waiting2:
              return "WAITING";
          }
        }
      })
    });

    onMounted(() => {
      state.elevator = new Elevator();
      state.history.push({
        state: "STANDBY",
        input: null,
        output: null
      });
    });

    function inputBtn(inVal: Button): void {
      const output = state?.elevator?.step(inVal);
      state.history.push({
        state: state.elevatorStateComputed,
        input: output?.in.toString(),
        output: ""
      });
    }

    function getImg(state: ElevatorState): __WebpackModuleApi.RequireContext {
      const images = require.context("../assets/elevator", false, /\.png$/);
      return images("./elevator-diagram-" + state + ".png");
    }

    function formatButton(btn: Button): string {
      if (btn == Button.a) {
        return "A";
      } else if (btn == Button.b) {
        return "B";
      } else if (btn == Button.c) {
        return "C";
      } else if (btn == Button.d) {
        return "D";
      } else if (btn == Button.e) {
        return "E";
      } else if (btn == Button.f) {
        return "F";
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
.state-pill {
  background-color: var(--vue-logo-green);
  padding: 10px;
}
.btn {
  border-radius: 6px;
}
</style>