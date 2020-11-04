<template>
  <div class="row text-center no-gutters mx-4 justify-content-center">
    <group-box title="Dijagram">
      <div class="col-12 mt-5">
        <img :src="require('@/assets/elevator/elevator-diagram-empty.png')" />
      </div>
    </group-box>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "vjezba-4"
});
</script>
