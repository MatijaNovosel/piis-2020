<template>
  <navbar />
  <div class="navbar-offset">
    <router-view />
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import navbar from "@/components/navbar.vue";

export default defineComponent({
  name: "App",
  components: {
    navbar
  },
  props: {
    msg: String
  }
});
</script>

<style>
.navbar-offset {
  margin-top: calc(var(--navbar-height) - 25px);
}
</style>
