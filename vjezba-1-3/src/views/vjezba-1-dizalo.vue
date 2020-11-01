<template>
  <div class="row text-center no-gutters justify-content-center">
    <div class="col-12">
      <span style="font-size: 20px" class="badge badge-pill badge-primary"
        >Vježba 1 - Dizalo</span
      >
    </div>
    <div class="col-4 mt-5">
      <group-box title="Dijagram">
        <img :src="require('../assets/elevator-diagram.png')" />
      </group-box>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, onMounted } from "vue";

export default defineComponent({
  name: "vjezba-1",
  setup() {
    onMounted(() => {
      //
    });

    return {};
  }
});
</script>